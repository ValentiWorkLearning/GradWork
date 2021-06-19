#pragma once
#include <atomic>
#include <condition_variable>
#include <coroutine>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

struct Promise
{
    auto initial_suspend() noexcept
    {
        return std::suspend_never{};
    }
    auto final_suspend() noexcept
    {
        return std::suspend_never{};
    }

    void get_return_object()
    {
    }
    void return_void()
    {
    }

    void unhandled_exception()
    {
        while (1)
        {
        }
    }
};

template <typename... Args> struct std::coroutine_traits<void, Args...>
{
    using promise_type = Promise;
};

namespace CoroUtils
{

template <typename TAwaiter> auto awaiterGetter(TAwaiter&& _awaiter)
{
    return static_cast<TAwaiter&&>(_awaiter).operator co_await();
}

template <typename TAwaitable> struct AwaitResultGetter
{
    using Type = decltype(awaiterGetter(std::declval<TAwaitable>()));
    using Result = decltype(std::declval<Type>().await_resume());
};

class BlockingEvent
{
public:
    void wait()
    {
        std::unique_lock<std::mutex> lock(mutex);
        condEvent.wait(lock, [this] { return m_isSet.load(std::memory_order_acquire); });
    }

    void set()
    {
        m_isSet.store(true, std::memory_order_release);
        condEvent.notify_all();
    }

private:
    std::atomic_bool m_isSet = false;
    std::mutex mutex;
    std::condition_variable condEvent;
};

template <typename TResultType> struct SyncWaitTask
{
    struct SyncTaskPromise;
    using promise_type = SyncTaskPromise;
    using TResultRef = TResultType&&;

    SyncWaitTask(std::coroutine_handle<SyncTaskPromise> _suspendedRoutine)
        : m_suspendedRoutine{_suspendedRoutine}
    {
    }
    ~SyncWaitTask()
    {
        if (m_suspendedRoutine)
            m_suspendedRoutine.destroy();
    }

    struct FinalAwaitable
    {
        bool await_ready() noexcept
        {
            return false;
        }
        template <typename TPromise>
        void await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
        {
            // по окончанию работы сопрограммы устанавливаем  blockingEvent  в set, тем самым
            // восстанавливая текущий поток выполнения
            SyncTaskPromise& promise = coroutine.promise();
            promise.m_event->set();
        }
        void await_resume() noexcept
        {
        }
    };

    struct SyncTaskPromise
    {

        auto get_return_object() noexcept
        {
            return SyncWaitTask{std::coroutine_handle<SyncTaskPromise>::from_promise(*this)};
        }
        void start(BlockingEvent* _pEvent) noexcept
        {
            m_event = _pEvent;
            std::coroutine_handle<SyncTaskPromise>::from_promise(*this).resume();
        }
        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }

        auto final_suspend() noexcept
        {
            return FinalAwaitable{};
        }

        auto yield_value(TResultRef result) noexcept
        {
            // для поддержки operator co_yield
            m_value = std::addressof(result);
            return final_suspend();
        }

        decltype(auto) value() noexcept
        {
            return static_cast<TResultRef>(*m_value);
        }

        void return_void() noexcept
        {
        }

        void unhandled_exception()
        {
            std::terminate();
        }

        BlockingEvent* m_event;
        std::remove_reference_t<TResultType>* m_value;
    };

    TResultType&& result() noexcept
    {
        return m_suspendedRoutine.promise().value();
    }

    void await_resume()
    {
    }

    void start(BlockingEvent& _event)
    {
        m_suspendedRoutine.promise().start(&_event);
    }
    std::coroutine_handle<SyncTaskPromise> m_suspendedRoutine;
};

template <
    typename TAwaitable,
    typename TTaskResult = typename AwaitResultGetter<TAwaitable>::Result>
SyncWaitTask<TTaskResult> makeSyncWaitTask(TAwaitable&& _awaitable)
{
    co_yield co_await _awaitable;
}

template <typename TResult> struct Task
{
    struct ResultTaskPromise;
    using promise_type = ResultTaskPromise;

    struct ResultTaskPromise
    {
        ResultTaskPromise() noexcept = default;

        void unhandled_exception() noexcept
        {
            while (true)
            {
            }
        }
        Task<TResult> get_return_object() noexcept
        {
            return Task<TResult>{std::coroutine_handle<ResultTaskPromise>::from_promise(*this)};
        }
        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }

        void return_value(const TResult& _value) noexcept
        {
            m_coroutineResult = _value;
        }

        void set_continuation(std::coroutine_handle<> continuation)
        {
            m_continuation = continuation;
        }

        TResult& result()
        {
            return m_coroutineResult;
        }

        struct final_awaitable
        {
            bool await_ready() noexcept
            {
                return false;
            }
            template <typename TPromise>
            void await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
            {
                ResultTaskPromise& promise = coroutine.promise();
                if (promise.m_continuation)
                {
                    promise.m_continuation.resume();
                }
            }

            void await_resume() noexcept
            {
            }
        };

        auto final_suspend() noexcept
        {
            return final_awaitable{};
        }

        TResult m_coroutineResult;
        std::coroutine_handle<> m_continuation;
    };

    struct task_awaitable
    {
        task_awaitable(std::coroutine_handle<promise_type> coroutine) : m_coroutine{coroutine}
        {
        }
        bool await_ready() const noexcept
        {
            return !m_coroutine || m_coroutine.done();
        }
        void await_suspend(std::coroutine_handle<> awaitingRoutine)
        {
            m_coroutine.promise().set_continuation(awaitingRoutine);
            m_coroutine.resume();
        }

        decltype(auto) await_resume()
        {
            return m_coroutine.promise().result();
        }

        std::coroutine_handle<promise_type> m_coroutine;
    };

    Task(std::coroutine_handle<ResultTaskPromise> suspendedCoroutine)
        : m_coroutine{suspendedCoroutine}
    {
    }

    ~Task()
    {
        if (m_coroutine)
            m_coroutine.destroy();
    }

    bool await_ready() const noexcept
    {
        return !m_coroutine || m_coroutine.done();
    }

    auto operator co_await() noexcept
    {
        return task_awaitable{m_coroutine};
    }

    void await_resume()
    {
    }

    std::coroutine_handle<promise_type> m_coroutine;
};

struct VoidTask
{
    struct task_promise;
    using promise_type = task_promise;

    struct task_promise
    {
        task_promise() noexcept = default;
        void return_void() noexcept
        {
        }
        void unhandled_exception() noexcept
        {
            while (true)
            {
            }
        }
        VoidTask get_return_object() noexcept
        {
            return VoidTask{std::coroutine_handle<task_promise>::from_promise(*this)};
        }

        auto initial_suspend() noexcept
        {
            return std::suspend_always{};
        }

        struct final_awaitable
        {
            bool await_ready() noexcept
            {
                return false;
            }
            template <typename TPromise>
            void await_suspend(std::coroutine_handle<TPromise> coroutine) noexcept
            {
                task_promise& promise = coroutine.promise();
                if (promise.m_continuation)
                {
                    promise.m_continuation.resume();
                }
            }

            void await_resume() noexcept
            {
            }
        };

        void set_continuation(std::coroutine_handle<> continuation)
        {
            m_continuation = continuation;
        }

        auto final_suspend() noexcept
        {
            return final_awaitable{};
        }

        std::coroutine_handle<> m_continuation;
    };

    struct task_awaitable
    {
        task_awaitable(std::coroutine_handle<promise_type> coroutine) : m_coroutine{coroutine}
        {
        }
        bool await_ready() const noexcept
        {
            return !m_coroutine || m_coroutine.done();
        }
        void await_suspend(std::coroutine_handle<> awaitingRoutine)
        {
            m_coroutine.resume();
            m_coroutine.promise().set_continuation(awaitingRoutine);
        }

        void await_resume()
        {
        }

        std::coroutine_handle<promise_type> m_coroutine;
    };

    VoidTask(std::coroutine_handle<task_promise> suspendedCoroutine)
        : m_coroutine{suspendedCoroutine}
    {
    }

    ~VoidTask()
    {
        if (m_coroutine)
            m_coroutine.destroy();
    }

    bool await_ready() const noexcept
    {
        return !m_coroutine || m_coroutine.done();
    }

    auto operator co_await() noexcept
    {
        return task_awaitable{m_coroutine};
    }

    void await_resume()
    {
    }

    std::coroutine_handle<promise_type> m_coroutine;
};

template <typename TCoroutine>
auto syncWait(TCoroutine&& _coroutineTask) ->
    typename AwaitResultGetter<decltype(static_cast<TCoroutine&&>(_coroutineTask))>::Result
{
    BlockingEvent waitOn;
    auto task = makeSyncWaitTask(_coroutineTask);
    task.start(waitOn);
    waitOn.wait();

    return task.result();
}

struct CoroQueueMainLoop
{
    static CoroQueueMainLoop& GetInstance()
    {
        static CoroQueueMainLoop instance{};
        return instance;
    }

    void pushToLater(std::coroutine_handle<> coroHandle)
    {
        executionQueue.push(coroHandle);
    }

    void processQueue()
    {

        while (!executionQueue.empty())
        {
            std::coroutine_handle<> coroHandle = executionQueue.front();
            if (!coroHandle.done())
            {
                executionQueue.pop();
                coroHandle.resume();
            }
        }
    }

    std::queue<std::coroutine_handle<>> executionQueue;
};

template <typename... Tasks> struct WhenAllSequence
{
    std::tuple<Tasks...> m_taskList;

    explicit WhenAllSequence(Tasks&&... tasks) noexcept : m_taskList(std::move(tasks)...)
    {
    }

    explicit WhenAllSequence(std::tuple<Tasks...>&& tasks) noexcept : m_taskList(std::move(tasks))
    {
    }

    bool await_ready() const noexcept
    {
        return false;
    }

    void await_suspend(std::coroutine_handle<> handle) noexcept
    {
        co_await launchAll(std::make_integer_sequence<std::size_t, sizeof...(Tasks)>{});
        handle.resume();
    }

    template <std::size_t... Indexes>
    VoidTask launchAll(std::integer_sequence<std::size_t, Indexes...>)
    {
        (co_await std::get<Indexes>(m_taskList), ...);
    }

    void await_resume() noexcept
    {
    }
};

template <typename... Args> auto when_all_sequence(Args&&... args) noexcept
{
    return WhenAllSequence{std::make_tuple(std::move(args)...)};
}

struct Event
{
    Event(bool isSet = false) : m_isSet{isSet}
    {
    }

    bool await_ready() noexcept
    {
        return m_isSet;
    }

    void await_suspend(std::coroutine_handle<> handle)
    {
        m_continuation = handle;
    }

    void await_resume()
    {
    }

    void set(bool toMainThread = false)
    {
        m_isSet.store(true);
        if (m_continuation && !m_continuation.done())
        {
            if (toMainThread)
            {
                CoroQueueMainLoop::GetInstance().pushToLater(m_continuation);
            }
            else
            {
                m_continuation.resume();
            }
        }
    }

    bool isSet() const noexcept
    {
        return m_isSet;
    }

    std::atomic_bool m_isSet;
    std::coroutine_handle<> m_continuation;
};

}; // namespace CoroUtils
