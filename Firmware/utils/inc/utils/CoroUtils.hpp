#pragma once

#include "MetaUtils.hpp"

#include <coroutine>
#include <atomic>
#include <array>
#include <logger/logger_service.hpp>

struct Promise
{
	auto initial_suspend()noexcept
	{
		return std::suspend_never{};
	}
	auto final_suspend()noexcept
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

template <typename... Args>
struct std::coroutine_traits<void, Args ...>
{
	using promise_type = Promise;
};


namespace CoroUtils
{

	struct VoidTask
	{
		struct task_promise;
		using promise_type = task_promise;

		struct task_promise
		{
			task_promise()noexcept = default;
			void return_void()noexcept {}
			void unhandled_exception() noexcept
			{
				while (true)
				{

				}
			}
			VoidTask get_return_object()noexcept
			{
				return VoidTask{ std::coroutine_handle<task_promise>::from_promise(*this) };
			}

			auto initial_suspend()noexcept { return std::suspend_always{}; }

			struct final_awaitable
			{
				bool await_ready()
				{
					return false;
				}
				template<typename TPromise>
				void await_suspend(std::coroutine_handle<TPromise> coroutine)
				{
					task_promise& promise = coroutine.promise();
					if (promise.m_continuation)
					{
						promise.m_continuation.resume();
					}
				}

				void await_resume() {}
			};

			void set_continuation(std::coroutine_handle<> continuation)
			{
				m_continuation = continuation;
			}

			auto final_suspend()
			{
				return final_awaitable{};
			}

			std::coroutine_handle<> m_continuation;
		};

		struct task_awaitable
		{
			task_awaitable(std::coroutine_handle<promise_type> coroutine)
				: m_coroutine{ coroutine }
			{
			}
			bool await_ready()const noexcept
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
			: m_coroutine{ suspendedCoroutine }
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
			return task_awaitable{ m_coroutine };
		}

		void await_resume()
		{
		}

		std::coroutine_handle<promise_type> m_coroutine;
	};

	template<typename ... Tasks>
	struct WhenAllSequence
	{
		std::tuple<Tasks...> m_taskList;

		explicit WhenAllSequence(Tasks&& ... tasks) noexcept
			: m_taskList(std::move(tasks)...)
		{
		}

		explicit WhenAllSequence(std::tuple<Tasks...>&& tasks)noexcept
			: m_taskList(std::move(tasks))
		{
		}

		bool await_ready() const noexcept { return false; }

		void await_suspend(std::coroutine_handle<> handle)
		{
			co_await std::apply(
				[](auto ... task)->VoidTask
				{
					(co_await task, ...);

					LOG_DEBUG("std::apply! completed\n");
				}
				, m_taskList
			);
			handle.resume();
			LOG_DEBUG("Requested coroutine resume\n");
		}

		void await_resume()
		{
		}
	};


	template<typename ... Args>
	auto when_all_sequence(Args&& ... args)
	{
		return WhenAllSequence{ std::make_tuple(std::move(args)...) };
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