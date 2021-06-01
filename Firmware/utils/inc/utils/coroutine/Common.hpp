#pragma once

#include "MetaUtils.hpp"

#include <array>
#include <atomic>
#include <coroutine>
#include <logger/logger_service.hpp>

#ifdef _MSC_VER
#include <coroutine>
#include <thread>
namespace stdcoro = std;
#elif __GNUC__
#include <coroutine>
namespace stdcoro = std;
#else
#include <experimental/coroutine>
namespace stdcoro = std::experimental
#endif

#include <etl/queue_spsc_atomic.h>
#include <etl/vector.h>

struct Promise
{
    auto initial_suspend() noexcept
    {
        return stdcoro::suspend_never{};
    }
    auto final_suspend() noexcept
    {
        return stdcoro::suspend_never{};
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

template <typename... Args> struct stdcoro::coroutine_traits<void, Args...>
{
    using promise_type = Promise;
};