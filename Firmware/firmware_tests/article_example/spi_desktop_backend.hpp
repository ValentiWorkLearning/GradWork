#pragma once

#include <array>
#include <cstdint>
#include <functional>
#include <iostream>

#include <span>
#include <vector>

class SpiBusDesktopBackend
{

public:
    SpiBusDesktopBackend() = default;

    ~SpiBusDesktopBackend() = default;

public:
    void sendChunk(const std::uint8_t* _pBuffer, const size_t _bufferSize) noexcept
    {
        m_dataBuffer = std::span(_pBuffer, _bufferSize);
        std::cout << "TRANSMIT SOME DATA:" << ' ';

        for (const auto block : m_dataBuffer)
        {
            std::cout << std::hex << static_cast<std::int16_t>(block) << ' ';
        }
        std::cout << std::endl;

        m_transactionCompleted();
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
    std::span<const std::uint8_t> m_dataBuffer;

    TTransactionCompletedHandler m_transactionCompleted;
};