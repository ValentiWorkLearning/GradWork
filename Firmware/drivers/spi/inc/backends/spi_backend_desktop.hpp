#pragma once

#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <span>
#include <fmt/ranges.h>

#include <utils/MetaUtils.hpp>

#define USE_THREADING_ASYNC_BACKEND

namespace Interface::SpiTemplated
{

class SpiBusDesktopBackend
{

public:
    SpiBusDesktopBackend()
        : m_newDataArrived{false}
        , m_dataBuffer{}
        , m_bufferTransmitSize{}
        , m_processSpiTransactions{true}
    {
#ifdef USE_THREADING_ASYNC_BACKEND

        m_dmaThread = std::make_unique<std::thread>([this]()mutable {
            while (m_processSpiTransactions)
            {
                if (m_newDataArrived)
                {
                    using namespace std::chrono_literals;

                    std::unique_lock<std::mutex>(m_transactionBufferGuard);
                    fmt::print("[Desktop SPI simultator]{}\n", m_dataBuffer);

                    m_newDataArrived.store(false);
                    m_transactionCompleted();
                }
            }
        });
#endif //  USE_THREADING_ASYNC_BACKEND
    }

    ~SpiBusDesktopBackend()
    {
        m_processSpiTransactions.store(false);
        m_dmaThread->detach();
        m_dmaThread.reset();
    }

public:

    void setCsPinHigh() noexcept
    {
    }

    void setCsPinLow() noexcept
    {
    }

    void sendChunk(const std::uint8_t* _pBuffer, const size_t _bufferSize) noexcept
    {
        m_bufferTransmitSize.store(_bufferSize);
        m_dataBuffer.clear();
        m_dataBuffer.reserve(_bufferSize);

        std::unique_lock<std::mutex>(m_transactionBufferGuard);
        std::copy(_pBuffer, _pBuffer + _bufferSize, std::back_inserter(m_dataBuffer));
        m_newDataArrived.store(true, std::memory_order_release);

#ifndef USE_THREADING_ASYNC_BACKEND
        std::cout << "TRANSMIT SOME DATA:" << ' ';

        for (size_t i{}; i < m_bufferTransmitSize; ++i)
        {
            std::cout << std::hex << static_cast<std::int16_t>(m_pDataBuffer[i]) << ' ';
        }
        std::cout << std::endl;

        m_newDataArrived.store(false);
        m_transactionCompleted();
#endif
    }

    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(TTransactionCompletedHandler&& _handler)
    {
        m_transactionCompleted = std::move(_handler);
    }

    void xferChunk(
        std::span<const std::uint8_t> _transmitArray,
        std::span<std::uint8_t> _receiveArray)
    {
    }

private:
    std::atomic_bool m_newDataArrived;
    std::atomic_bool m_processSpiTransactions;
    mutable std::mutex m_transactionBufferGuard;
    std::vector<std::uint8_t> m_dataBuffer;
    std::atomic<size_t> m_bufferTransmitSize;

    std::unique_ptr<std::thread> m_dmaThread;
    TTransactionCompletedHandler m_transactionCompleted;
};
} // namespace Interface::SpiTemplated