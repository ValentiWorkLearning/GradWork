#pragma once

#include "Common.hpp"

namespace CoroUtils
{
 struct WhenAllReadyCounter
{
    WhenAllReadyCounter(size_t _countTo)
        :   m_suspendedCoroutine{nullptr}
        ,   m_whenAllCounter{ _countTo +1}
    {
    }

    void setCoroutineForWaiting( std::coroutine_handle<> _awaitingCoroutine )noexcept
    {
        m_suspendedCoroutine = _awaitingCoroutine;
        m_whenAllCounter.fetch_sub(1, std::memory_order_acq_rel);
    }

    void notifyAwaitingCompleted()noexcept
    {
        const size_t countValue{ m_whenAllCounter.fetch_sub(1,std::memory_order_acq_rel) };
        if(countValue == 1)
        {
            m_suspendedCoroutine.resume();
        }
    }

    std::coroutine_handle<> m_suspendedCoroutine;
    std::atomic<size_t> m_whenAllCounter;
};

 template<typename Task>
 struct WhenAllTask
{
    WhenAllTask(Task _task)
        :   m_taskItem{ _task }
        ,   m_whenAllCounter{nullptr}
    {
    }
    bool await_ready() const noexcept
    {
        return false;
    }

    void await_resume() const noexcept
    {
        m_whenAllCounter->notifyAwaitingCompleted();
    }

    void await_suspend(std::coroutine_handle<> thisCoroutine) noexcept
    {
        co_await m_taskItem;
        thisCoroutine.resume();
    }

    void setTimer(WhenAllReadyCounter* _pCounter)
    {
       m_whenAllCounter = _pCounter;
    }

    Task m_taskItem;
    WhenAllReadyCounter* m_whenAllCounter;
};

 template<typename ...Awaitables>
 auto when_all(Awaitables&&... _awaitablesList)
{
    struct WhenAllAwaitable
    {

        using TTaskTuple = std::tuple<WhenAllTask<Awaitables>...>;
        TTaskTuple m_taskList;
        WhenAllReadyCounter m_whenAllCounter;

        bool await_ready() const noexcept
        {
            return false;
        }
        TTaskTuple& await_resume()noexcept
        {
            return m_taskList;
        }

        void await_suspend(std::coroutine_handle<> thisCoroutine) noexcept
        {
            m_whenAllCounter.setCoroutineForWaiting(thisCoroutine);
            std::apply(
                    [this](auto& ... task)
                    {
                        (task.setTimer(&m_whenAllCounter), ...);
                    }
                ,   m_taskList
            );
            std::apply(
                    [](auto&... _task)
                    {
                        return makeTaskSequence(_task...);
                    }
                ,   m_taskList
            );
        }
    };

    return WhenAllAwaitable{
            std::forward_as_tuple(_awaitablesList...)
        ,   sizeof...(_awaitablesList)
    };
}

}