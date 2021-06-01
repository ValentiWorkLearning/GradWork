#pragma once
#include "Event.hpp"
#include "Task.hpp"

namespace CoroUtils
{

template <typename TCoroutine>
auto syncWait(TCoroutine&& _coroutineTask) ->decltype(
    static_cast<TCoroutine&&>(_coroutineTask).operator co_await())
{
    //Event waitOn;
    //auto task = makeSyncWaitTask(_coroutineTask);
    //task.start(waitOn);
    //waitOn.wait();

    //return task.result();
    return decltype(static_cast<TCoroutine&&>(_coroutineTask).operator co_await()){};
}

} // namespace CoroUtils