#pragma once

#include <functional>
#include <queue>
#include <ranges>
#include <span>
#include <vector>

#include <utils/CoroUtils.hpp>

namespace Testing::Spi
{

class SpiBusBackendStub
{

public:
    void sendChunk(const std::uint8_t* _pBuffer, const size_t _bufferSize) noexcept
    {
        BusTransactionsTransmit.emplace_back(_pBuffer, _bufferSize);
        m_completedTransaction();
    }

    void receiveChunk(std::uint8_t* _pDestinationArray, size_t _receiveSize)
    {
        auto arraySpan = std::span(_pDestinationArray, _receiveSize);
        std::ranges::transform(
            m_dataStreamReceived.begin(),
            m_dataStreamReceived.begin() + _receiveSize,
            arraySpan.begin(),
            [](const std::byte _byte) { return static_cast<std::uint8_t>(_byte); });

        m_completedTransaction();
    }

    void xferChunk(
        std::span<const std::uint8_t> _transmitArray,
        std::span<std::uint8_t> _receiveArray)
    {
        BusTransactionsTransmit.emplace_back(_transmitArray.data(), _transmitArray.size());
        BusTransactionsTransmit.emplace_back(_transmitArray.data(), _receiveArray.size());

        auto streamSpan = std::span(
            reinterpret_cast<const std::uint8_t*>(m_dataStreamReceived.data()),
            m_dataStreamReceived.size());

        BusTransactionsReceive.emplace_back(streamSpan.data(), streamSpan.size());
        std::ranges::copy(streamSpan, _receiveArray.begin());

        m_completedTransaction();
    }

    void setCsPinHigh() noexcept
    {
    }

    void setCsPinLow() noexcept
    {
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
        std::for_each(
            BusTransactionsTransmit.cbegin(),
            BusTransactionsTransmit.cend(),
            [&stream](const auto& _transaction) {
                const auto& [pArray, blockSize] = _transaction;
                auto arraySpan = std::span{pArray, blockSize};
                std::transform(
                    arraySpan.begin(),
                    arraySpan.end(),
                    std::back_inserter(stream),
                    [](std::uint8_t _dataByte) { return std::byte{_dataByte}; });
            });
        return stream;
    }

    void setReceivedStream(const TDataStream& _receivedStream)
    {
        m_dataStreamReceived = _receivedStream;
    }

protected:
    using TTransacation = std::pair<const std::uint8_t*, size_t>;
    std::vector<TTransacation> BusTransactionsTransmit;
    std::vector<TTransacation> BusTransactionsReceive;

private:
    TTransactionCompletedHandler m_completedTransaction;
    TDataStream m_dataStreamReceived;
};

} // namespace Testing::Spi