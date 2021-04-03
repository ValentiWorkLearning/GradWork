//#include "ap_application.hpp"
//#include <etl/memory.h>
//#include "utils/CoroutineExample.hpp"

#include <string>
#include <coroutine>

#include "SEGGER_RTT.h"

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

private:
    coro_handle m_handle;
};

constexpr inline auto FirstMessage = "Before suspending";
constexpr inline auto SecondMessage = "After restoring from suspended state";

Resumable suspendableFunction() noexcept
{
    SEGGER_RTT_WriteString(0, FirstMessage);
    co_await std::suspend_always{};
    SEGGER_RTT_WriteString(0, SecondMessage);
}

int main(void)
{
    auto resumable = suspendableFunction();
    resumable.resume();
    resumable.resume();

    while (true)
    {
    }
    return 0;
}