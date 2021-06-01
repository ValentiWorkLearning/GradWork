#pragma once
#include "Common.hpp"

namespace CoroUtils
{

template <typename... Tasks> struct WhenAllSequence
{
    std::tuple<Tasks...> m_taskList;

    explicit WhenAllSequence(Tasks&&... tasks) noexcept : m_taskList(std::move(tasks)...)
    {
    }

    explicit WhenAllSequence(std::tuple<Tasks...>&& tasks) noexcept : m_taskList(std::move(tasks))
    {
    }

    bool await_ready() const noexcept
    {
        return false;
    }

    void await_suspend(stdcoro::coroutine_handle<> handle) noexcept
    {
        co_await launchAll(std::make_integer_sequence<std::size_t, sizeof...(Tasks)>{});
        handle.resume();
    }

    template <std::size_t... Indexes>
    VoidTask launchAll(std::integer_sequence<std::size_t, Indexes...>)
    {
        (co_await std::get<Indexes>(m_taskList), ...);
    }

    void await_resume() noexcept
    {
    }
};

template <typename... Args> auto when_all_sequence(Args&&... args) noexcept
{
    return WhenAllSequence{std::make_tuple(std::move(args)...)};
}

} // namespace CoroUtils