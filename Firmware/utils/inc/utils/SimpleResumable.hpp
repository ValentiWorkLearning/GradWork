#pragma once
#include <etl/memory.h>
#include <coroutine>

class Resumable
{
public:
    struct promise_type;
    using coro_handle = std::coroutine_handle<promise_type>;

    Resumable(coro_handle coroutineHandle) noexcept
        : m_handle{coroutineHandle}
    {
    }
    ~Resumable() { m_handle.destroy(); }

public:
    void resume(){ if (!m_handle.done()) m_handle.resume();}
    struct promise_type
    {
        auto get_return_object() noexcept { return coro_handle::from_promise(*this);}
        auto initial_suspend() noexcept { return std::suspend_always{};}
        auto final_suspend() noexcept{ return std::suspend_always{};}
        void return_void() noexcept {}
        void unhandled_exception() noexcept{}
    };

    constexpr coro_handle getSuspendedCoroHandle()const
    {
        return m_handle;
    }

private:
    coro_handle m_handle;
};