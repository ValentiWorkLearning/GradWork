#pragma once
#include "Common.hpp"

namespace CoroUtils
{

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
            return Task<TResult>{stdcoro::coroutine_handle<ResultTaskPromise>::from_promise(*this)};
        }
        auto initial_suspend() noexcept
        {
            return stdcoro::suspend_always{};
        }

        void return_value(const TResult& _value) noexcept
        {
            m_coroutineResult = _value;
        }

        void set_continuation(stdcoro::coroutine_handle<> continuation)
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
            void await_suspend(stdcoro::coroutine_handle<TPromise> coroutine) noexcept
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
        stdcoro::coroutine_handle<> m_continuation;
    };

    struct task_awaitable
    {
        task_awaitable(stdcoro::coroutine_handle<promise_type> coroutine) : m_coroutine{coroutine}
        {
        }
        bool await_ready() const noexcept
        {
            return !m_coroutine || m_coroutine.done();
        }
        void await_suspend(stdcoro::coroutine_handle<> awaitingRoutine)
        {
            m_coroutine.promise().set_continuation(awaitingRoutine);
            m_coroutine.resume();
        }

        decltype(auto) await_resume()
        {
            return m_coroutine.promise().result();
        }

        stdcoro::coroutine_handle<promise_type> m_coroutine;
    };

    Task(stdcoro::coroutine_handle<ResultTaskPromise> suspendedCoroutine)
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

    stdcoro::coroutine_handle<promise_type> m_coroutine;
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
            return VoidTask{stdcoro::coroutine_handle<task_promise>::from_promise(*this)};
        }

        auto initial_suspend() noexcept
        {
            return stdcoro::suspend_always{};
        }

        struct final_awaitable
        {
            bool await_ready() noexcept
            {
                return false;
            }
            template <typename TPromise>
            void await_suspend(stdcoro::coroutine_handle<TPromise> coroutine) noexcept
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

        void set_continuation(stdcoro::coroutine_handle<> continuation)
        {
            m_continuation = continuation;
        }

        auto final_suspend() noexcept
        {
            return final_awaitable{};
        }

        stdcoro::coroutine_handle<> m_continuation;
    };

    struct task_awaitable
    {
        task_awaitable(stdcoro::coroutine_handle<promise_type> coroutine) : m_coroutine{coroutine}
        {
        }
        bool await_ready() const noexcept
        {
            return !m_coroutine || m_coroutine.done();
        }
        void await_suspend(stdcoro::coroutine_handle<> awaitingRoutine)
        {
            m_coroutine.resume();
            m_coroutine.promise().set_continuation(awaitingRoutine);
        }

        void await_resume()
        {
        }

        stdcoro::coroutine_handle<promise_type> m_coroutine;
    };

    VoidTask(stdcoro::coroutine_handle<task_promise> suspendedCoroutine)
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

    stdcoro::coroutine_handle<promise_type> m_coroutine;
};

} // namespace CoroUtils