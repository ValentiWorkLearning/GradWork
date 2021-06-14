#pragma once

#include <functional>
#include <queue>
#include <ranges>
#include <span>
#include <vector>

#include <utils/CoroUtils.hpp>
#include "mock_gpio.hpp"
#include "mock_spi.hpp"

namespace Testing::Spi
{

class SpiBusBackendStub
{

public:
    void sendChunk(const std::uint8_t* _pBuffer, const size_t _bufferSize) noexcept
    {
        BusTransactionsTransmit.emplace_back(_pBuffer, _bufferSize);
        m_spiMocker.sentData(std::span(_pBuffer,_bufferSize));
        m_completedTransaction();
    }

    void receiveChunk(std::uint8_t* _pDestinationArray, size_t _receiveSize)
    {
        const auto& receivedRange = m_spiMocker.receivedData();
        auto arraySpan = std::span(_pDestinationArray, _receiveSize);
        std::ranges::copy_n(receivedRange.begin(), _receiveSize, arraySpan.begin() );

        m_completedTransaction();
    }

    void xferChunk(
        std::span<const std::uint8_t> _transmitArray,
        std::span<std::uint8_t> _receiveArray)
    {
        BusTransactionsTransmit.emplace_back(_transmitArray.data(), _transmitArray.size());
        BusTransactionsTransmit.emplace_back(_receiveArray.data(), _receiveArray.size());

        m_spiMocker.sentData(std::span(_transmitArray.data(), _transmitArray.size()));
        const auto& receivedRange = m_spiMocker.receivedData();

        auto streamSpan = std::span(
            reinterpret_cast<const std::uint8_t*>(receivedRange.data()),
            receivedRange.size());

        BusTransactionsReceive.emplace_back(streamSpan.data(), streamSpan.size());
        std::ranges::copy(streamSpan, _receiveArray.begin());

        m_completedTransaction();
    }

    void setCsPinHigh() noexcept
    {
        m_csPin.setGpioHigh();
    }

    void setCsPinLow() noexcept
    {
        m_csPin.setGpioLow();
    }

public:
    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(TTransactionCompletedHandler&& _handler)
    {
        m_completedTransaction = std::move(_handler);
    }

    size_t getTransactionsSize() const
    {
        return BusTransactionsTransmit.size();
    }

    using TDataStream = std::vector<std::byte>;
    TDataStream getTransmittedData() const
    {
        TDataStream stream;
        std::ranges::for_each(
            BusTransactionsTransmit,
            [&stream](const auto& _transaction) {
                const auto& [pArray, blockSize] = _transaction;
                auto arraySpan = std::span{pArray, blockSize};
                std::ranges::transform(
                    arraySpan,
                    std::back_inserter(stream),
                    [](std::uint8_t _dataByte) { return std::byte{_dataByte}; });
            });
        return stream;
    }

    using TCSPinAccessor = testing::NiceMock<Gpio::MockGpio>;
    using TMockerSpi = testing::NiceMock<SpiMock::SpiMocker>;

    TCSPinAccessor& accesToCsPin()
    {
        return m_csPin;
    }

    const TCSPinAccessor& accesToCsPin() const
    {
        return m_csPin;
    }

    TMockerSpi& accessToSpiMock()
    {
        return m_spiMocker;
    }

    const TMockerSpi& accessToSpiMock() const
    {
        return m_spiMocker;
    }


protected:
    using TTransacation = std::pair<const std::uint8_t*, size_t>;
    std::vector<TTransacation> BusTransactionsTransmit;
    std::vector<TTransacation> BusTransactionsReceive;

private:
    TTransactionCompletedHandler m_completedTransaction;
    TCSPinAccessor m_csPin;
    TMockerSpi m_spiMocker;
};

} // namespace Testing::Spi