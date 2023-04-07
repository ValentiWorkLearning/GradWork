#pragma once
#include "Common.hpp"

namespace CoroUtils
{

struct CoroQueueMainLoop
{
    static CoroQueueMainLoop& GetInstance()
    {
        static CoroQueueMainLoop instance{};
        return instance;
    }

    void pushToLater(stdcoro::coroutine_handle<> coroHandle)
    {
        executionQueue.push(coroHandle);
    }

    void processQueue()
    {
        stdcoro::coroutine_handle<> handle;
        while (executionQueue.pop(handle))
        {
            if (!handle.done())
                handle.resume();
        }
    }

    template <typename Type, const size_t StorageSize = 3>
    using TQueueStorageType =
        etl::queue_spsc_atomic<Type, StorageSize, etl::memory_model::MEMORY_MODEL_SMALL>;

    TQueueStorageType<stdcoro::coroutine_handle<>> executionQueue;
};

} // namespace CoroUtils