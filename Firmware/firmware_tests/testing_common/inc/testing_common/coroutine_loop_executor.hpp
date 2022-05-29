#pragma once

#include <stop_token>
#include <thread>
#include <memory>
#include <utils/coroutine/ExecutionQueueCoro.hpp>

namespace Testing::Common
{
class CoroutineLoopExecutor
{
public:
    void startCoroLoop()
    {

        m_coroLoopWorker = std::make_unique<std::jthread>([stopSource = m_stopSource.get_token()] {
            while (!stopSource.stop_requested())
            {
                CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
            }
        });
    }

    void stopCoroutineLoop()
    {
        m_stopSource.request_stop();
    }

private:
    std::stop_source m_stopSource;
    std::unique_ptr<std::jthread> m_coroLoopWorker;

};

}