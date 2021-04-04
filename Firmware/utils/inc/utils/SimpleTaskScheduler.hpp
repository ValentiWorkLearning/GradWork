#pragma once

#include <utils/Noncopyable.hpp>

#include "SimpleResumable.hpp"

#include <coroutine>
#include <etl/queue.h>
#include <etl/vector.h>

namespace TaskScheduler
{

class SimpleCooperativeNonPriorityScheduler
{

public:

    void pushTask(Resumable::coro_handle taskHandle)
    {
        m_tasksStorage.push_back(taskHandle);
    }

    void runTasks()
    {
        while(true){
            size_t newTaskIndex = getTaskIndex();
            m_tasksStorage[newTaskIndex].resume();
        }
    }

    size_t getTaskIndex()
    {
        if (m_taskRunningIndex == m_tasksStorage.size())
            m_taskRunningIndex = 0;
        return m_taskRunningIndex++;
    }
private:

    template<typename Type, const size_t StorageSize = 6>
    using TStorageType = etl::vector<Type, StorageSize>;

    using TTaskStorage = TStorageType<Resumable::coro_handle>;

    TTaskStorage m_tasksStorage;
    size_t m_taskRunningIndex = 0;
};


}; // namespace TaskScheduler