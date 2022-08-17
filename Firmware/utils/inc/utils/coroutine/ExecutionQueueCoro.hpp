#pragma once
#include "Common.hpp"
#include <utils/CoroUtils.hpp>

namespace CoroUtils
{

struct CoroQueueMainLoop
{
    static CoroQueueMainLoop& GetInstance()
    {
        static CoroQueueMainLoop instance{};
        return instance;
    }

    void pushToLater(std::coroutine_handle<> coroHandle)
    {
        executionQueue.push(coroHandle);
    }

    void processQueue()
    {
        std::coroutine_handle<> handle;
        while (executionQueue.pop(handle))
        {
            if (!handle.done())
                handle.resume();
        }
    }

private:
    template <typename Type, const size_t StorageSize = 3>
    using TQueueStorageType =
        etl::queue_spsc_atomic<Type, StorageSize, etl::memory_model::MEMORY_MODEL_SMALL>;

    TQueueStorageType<std::coroutine_handle<>> executionQueue;
};

} // namespace CoroUtils