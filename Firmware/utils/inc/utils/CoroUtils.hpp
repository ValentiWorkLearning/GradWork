#pragma once
#ifdef WIN32
#include <experimental/coroutine>
namespace stdcoro = std::experimental;
#else
#include <coroutine>
namespace stdcoro = std;
#endif // WIN32

#include "MetaUtils.hpp"

namespace CoroUtils
{
template<typename ...Awaitables>
constexpr auto when_all(Awaitables&&... _awaitablesList)
{
	struct WhenAllAwaitable
	{
        std::tuple<Awaitables...> m_awaitablesList;

        bool await_ready() const noexcept
        {
            return false;
        }
        void await_resume() const noexcept
        {
        }
        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const
        {
            Meta::tupleApply(
                [thisCoroutine](auto&& _awaitable)
                {
                    co_await _awaitable;
                }
                ,   m_awaitablesList
            );
        }
	};

	return WhenAllAwaitable{
		std::forward_as_tuple(_awaitablesList...)
	};
}

}