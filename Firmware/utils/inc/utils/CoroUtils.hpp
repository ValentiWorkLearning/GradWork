#pragma once
#ifdef WIN32
#include <experimental/coroutine>
namespace stdcoro = std::experimental;
#else
#include <coroutine>
namespace stdcoro = std;
#endif // WIN32

#include "MetaUtils.hpp"
#include <atomic>

template <typename... Args>
struct stdcoro::coroutine_traits<void, Args...> {
    struct promise_type {
        void get_return_object() {}
        stdcoro::suspend_never initial_suspend() { return {}; }
        stdcoro::suspend_never final_suspend()noexcept { return {}; }
        void return_void() {}
        void unhandled_exception() { std::terminate(); }
    };
};


namespace CoroUtils
{


template<typename... Tasks>
void makeTaskSequence(Tasks&&... tasks)
{
    //Eventually, this should be compiled by GCC version >= 10.2 because of internal compiler error in GCC
#ifdef WIN32
    (co_await tasks, ...);

#else
    //Let's make some C++11

#endif

}
struct WhenAllReadyCounter
{
    WhenAllReadyCounter(size_t _countTo)
        :   m_suspendedCoroutine{nullptr}
        ,   m_whenAllCounter{ _countTo +1}
    {
    }

    void setCoroutineForWaiting( stdcoro::coroutine_handle<> _awaitingCoroutine )noexcept
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

    stdcoro::coroutine_handle<> m_suspendedCoroutine;
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

    void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) noexcept
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

        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) noexcept
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
                        //return makeCountedSequence(m_whenAllCounter, _taskList...);
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