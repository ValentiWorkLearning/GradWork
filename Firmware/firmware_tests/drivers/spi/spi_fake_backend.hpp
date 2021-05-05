#pragma once

#include <vector>
#include <functional>
#include <queue>
#include <span>

namespace Testing::Spi
{

class SpiBusBackendStub
{

public:

    void sendChunk(
        const std::uint8_t* _pBuffer
        , const size_t _bufferSize
    )noexcept
    {
        BusTransactions.emplace_back(_pBuffer, _bufferSize);
        m_completedTransaction();
    }

public:

    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(TTransactionCompletedHandler&& _handler)
    {
        m_completedTransaction = std::move(_handler);
    }

    size_t getTransactionsSize()const
    {
        return BusTransactions.size();
    }

    using TDataStream = std::vector<std::byte>;
    TDataStream getTransmittedData()const
    {
        TDataStream stream;
        std::for_each(
            BusTransactions.cbegin(),
            BusTransactions.cend(),
            [&stream](const auto& _transaction)
            {
                const auto& [pArray, blockSize] = _transaction;
                auto arraySpan = std::span{ pArray,blockSize };
                std::transform(
                    arraySpan.begin(),
                    arraySpan.end(),
                    std::back_inserter(stream),
                    [](std::uint8_t _dataByte) {
                        return std::byte{ _dataByte };
                    }
                );
            }
        );
        return stream;
    }

protected:
    using TTransacation = std::pair<const std::uint8_t*, size_t>;
    std::vector<TTransacation> BusTransactions;

private:

    TTransactionCompletedHandler m_completedTransaction;
};

} // namespace Testing::Spi