#pragma once
#include "Common.hpp"
#include "ExecutionQueueCoro.hpp"

namespace CoroUtils
{

struct Event
{
    Event(bool isSet = false) : m_isSet{isSet}
    {
    }

    bool await_ready() noexcept
    {
        return m_isSet;
    }

    void await_suspend(stdcoro::coroutine_handle<> handle)
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
    stdcoro::coroutine_handle<> m_continuation;
};

} // namespace CoroUtils