#pragma once

#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cstdint>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <mutex>
#include <condition_variable>

#include <utils/MetaUtils.hpp>

#define USE_THREADING_ASYNC_BACKEND


namespace Interface::SpiTemplated
{

class SpiBusDesktopBackend
{

public:
    SpiBusDesktopBackend()
        :   m_newDataArrived{ false }
        ,   m_pDataBuffer{ nullptr }
        ,   m_bufferTransmitSize{}
        ,   m_processSpiTransactions{true}
    {
#ifdef  USE_THREADING_ASYNC_BACKEND

        m_dmaThread = std::make_unique<std::thread>(
            [this]
            {
                while (m_processSpiTransactions)
                {
                    if(m_newDataArrived)
                    {
                        using namespace std::chrono_literals;
                        //std::this_thread::sleep_for(1500ms);

                        std::cout << "TRANSMIT SOME DATA:" << ' ';

                        for (size_t i{}; i < m_bufferTransmitSize; ++i)
                        {
                            std::cout << std::hex << static_cast<std::int16_t>(m_pDataBuffer[i]) << ' ';
                        }
                        std::cout << std::endl;

                        m_newDataArrived.store(false);
                        m_transactionCompleted();
                    }
                }
            }
       );
#endif  //  USE_THREADING_ASYNC_BACKEND
    }

    ~SpiBusDesktopBackend()
    {
        m_processSpiTransactions.store(false);
        m_dmaThread->detach();
        m_dmaThread.reset();
    }

public:

    void sendChunk(
        const std::uint8_t* _pBuffer
        , const size_t _bufferSize
    )noexcept
    {
        m_bufferTransmitSize.store( _bufferSize );
        m_pDataBuffer.store( _pBuffer );
        m_newDataArrived.store( true, std::memory_order_release );

#ifndef USE_THREADING_ASYNC_BACKEND
        std::cout << "TRANSMIT SOME DATA:" << ' ';

        for ( size_t i{}; i < m_bufferTransmitSize; ++i )
        {
            std::cout << std::hex
                      << static_cast<std::int16_t>( m_pDataBuffer[i] ) << ' ';
        }
        std::cout << std::endl;

        m_newDataArrived.store( false );
        m_transactionCompleted();
#endif
    }

    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(TTransactionCompletedHandler&& _handler)
    {
        m_transactionCompleted = std::move(_handler);
    }

private:

    std::atomic_bool m_newDataArrived;
    std::atomic_bool m_processSpiTransactions;
    std::atomic<const std::uint8_t*> m_pDataBuffer;
    std::atomic<size_t> m_bufferTransmitSize;

    std::unique_ptr<std::thread> m_dmaThread;
    TTransactionCompletedHandler m_transactionCompleted;
};
}