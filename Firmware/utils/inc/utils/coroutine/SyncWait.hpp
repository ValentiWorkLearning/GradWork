#pragma once
#include "Event.hpp"
#include "Task.hpp"

// Detailed research from cppcoro library
#include <condition_variable>
#include <mutex>

namespace CoroUtils
{

template <typename TAwaiter>
auto awaiterGetterImpl(TAwaiter&& _awaiter, int)
    -> decltype(static_cast<TAwaiter&&>(_awaiter).operator co_await())
{
    return static_cast<TAwaiter&&>(_awaiter).operator co_await();
}

template <typename TAwaiter>
auto awaiterGetterImpl(TAwaiter&& _awaiter, long)
    -> decltype(operator co_await(static_cast<TAwaiter&&>(_awaiter)))
{
    return operator co_await(static_cast<TAwaiter&&>(_awaiter));
}

template <typename TAwaiter>
auto awaiterGetter(TAwaiter&& _awaiter) -> decltype(awaiterGetterImpl(_awaiter,0))
{
    return awaiterGetterImpl(static_cast<TAwaiter&&>(_awaiter), 0);
}


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

template <typename TAwaitable> struct AwaitResultGetter
{
    using Type = decltype(awaiterGetter(std::declval<TAwaitable>()));
    using Result = decltype(std::declval<Type>().await_resume());
};

template <typename TResultType> struct SyncWaitTask
{
    struct SyncTaskPromise;
    using promise_type = SyncTaskPromise;
    using TResultRef = TResultType&&;

    SyncWaitTask(stdcoro::coroutine_handle<SyncTaskPromise> _suspendedRoutine)
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
        void await_suspend(stdcoro::coroutine_handle<TPromise> coroutine) noexcept
        {
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
            return SyncWaitTask{stdcoro::coroutine_handle<SyncTaskPromise>::from_promise(*this)};
        }
        void start(BlockingEvent* _pEvent) noexcept
        {
            m_event = _pEvent;
            stdcoro::coroutine_handle<SyncTaskPromise>::from_promise(*this).resume();
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
    stdcoro::coroutine_handle<SyncTaskPromise> m_suspendedRoutine;
};

template <typename TAwaitable, typename TTaskResult = AwaitResultGetter<TAwaitable>::Result>
SyncWaitTask<TTaskResult> makeSyncWaitTask(TAwaitable&& _awaitable)
{
    co_yield co_await _awaitable;
}
} // namespace CoroUtils

namespace CoroUtils
{

template <typename TCoroutine>
auto syncWait(TCoroutine&& _coroutineTask)
    -> AwaitResultGetter<decltype(static_cast<TCoroutine&&>(_coroutineTask))>::Result
{
    BlockingEvent waitOn;
    auto task = makeSyncWaitTask(_coroutineTask);
    task.start(waitOn);
    waitOn.wait();

    return task.result();
}

} // namespace CoroUtils