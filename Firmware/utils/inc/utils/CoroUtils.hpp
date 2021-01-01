#pragma once

#include "MetaUtils.hpp"

#include <coroutine>
#include <atomic>
#include <array>

struct Promise
{
	auto initial_suspend()noexcept
	{
		printf("Initial suspend \n");
		return std::suspend_never{};
	}
	auto final_suspend()noexcept
	{
		printf("Final suspend \n");
		return std::suspend_never{};
	}

	void get_return_object()
	{
		printf("void get_return_object() \n");
	}
	void return_void()
	{
		printf("void return_void() \n");
	}

	void unhandled_exception()
	{
		while (1)
		{

		}
	}

};

template <typename... Args>
struct std::coroutine_traits<void, Args ...>
{
	using promise_type = Promise;
};



namespace CoroUtils
{
	template<typename Task>
	struct WhenAllSequence
	{
		std::vector<Task> m_taskList;

		bool await_ready() const noexcept { return false; }

		void await_suspend(std::coroutine_handle<> handle)
		{
			for (auto& task : m_taskList)
			{
				co_await task;
			}
			handle.resume();
		}

		void await_resume()
		{
		}
	};


	template<typename Task, typename ... Args>
	auto when_all_sequence(Args&& ... args)
	{
		std::vector<Task> m_taskList;
		(m_taskList.push_back(std::forward<Args&&>(args)), ...);

		return WhenAllSequence{ std::move(m_taskList) };
	}

//
//template<typename... Tasks>
//void makeTaskSequence(Tasks&&... tasks)
//{
//    (co_await tasks, ...);
//}
//struct WhenAllReadyCounter
//{
//    WhenAllReadyCounter(size_t _countTo)
//        :   m_suspendedCoroutine{nullptr}
//        ,   m_whenAllCounter{ _countTo +1}
//    {
//    }
//
//    void setCoroutineForWaiting( std::coroutine_handle<> _awaitingCoroutine )noexcept
//    {
//        m_suspendedCoroutine = _awaitingCoroutine;
//        m_whenAllCounter.fetch_sub(1, std::memory_order_acq_rel);
//    }
//
//    void notifyAwaitingCompleted()noexcept
//    {
//        const size_t countValue{ m_whenAllCounter.fetch_sub(1,std::memory_order_acq_rel) };
//        if(countValue == 1)
//        {
//            m_suspendedCoroutine.resume();
//        }
//    }
//
//    std::coroutine_handle<> m_suspendedCoroutine;
//    std::atomic<size_t> m_whenAllCounter;
//};
//
//template<typename Task>
//struct WhenAllTask
//{
//    WhenAllTask(Task _task)
//        :   m_taskItem{ _task }
//        ,   m_whenAllCounter{nullptr}
//    {
//    }
//    bool await_ready() const noexcept
//    {
//        return false;
//    }
//
//    void await_resume() const noexcept
//    {
//        m_whenAllCounter->notifyAwaitingCompleted();
//    }
//
//    void await_suspend(std::coroutine_handle<> thisCoroutine) noexcept
//    {
//        co_await m_taskItem;
//        thisCoroutine.resume();
//    }
//
//    void setTimer(WhenAllReadyCounter* _pCounter)
//    {
//       m_whenAllCounter = _pCounter;
//    }
//
//    Task m_taskItem;
//    WhenAllReadyCounter* m_whenAllCounter;
//};
//
//template<typename ...Awaitables>
//auto when_all(Awaitables&&... _awaitablesList)
//{
//    struct WhenAllAwaitable
//    {
//
//        using TTaskTuple = std::tuple<WhenAllTask<Awaitables>...>;
//        TTaskTuple m_taskList;
//        WhenAllReadyCounter m_whenAllCounter;
//
//        bool await_ready() const noexcept
//        {
//            return false;
//        }
//        TTaskTuple& await_resume()noexcept
//        {
//            return m_taskList;
//        }
//
//        void await_suspend(std::coroutine_handle<> thisCoroutine) noexcept
//        {
//            m_whenAllCounter.setCoroutineForWaiting(thisCoroutine);
//            std::apply(
//                    [this](auto& ... task)
//                    {
//                        (task.setTimer(&m_whenAllCounter), ...);
//                    }
//                ,   m_taskList
//            );
//            std::apply(
//                    [](auto&... _task)
//                    {
//                        //return makeCountedSequence(m_whenAllCounter, _taskList...);
//                        return makeTaskSequence(_task...);
//                    }
//                ,   m_taskList
//            );
//        }
//    };
//
//    return WhenAllAwaitable{
//            std::forward_as_tuple(_awaitablesList...)
//        ,   sizeof...(_awaitablesList)
//    };
//}

}