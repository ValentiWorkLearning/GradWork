#pragma once

#include <vector>
#include <functional>
#include <queue>

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
        BusTransactions.emplace(_pBuffer, _bufferSize);
    }

public:

    using TTransactionCompletedHandler = std::function<void()>;
    void setTransactionCompletedHandler(TTransactionCompletedHandler&& _handler)
    {
        m_completedTransaction = std::move(_handler);
    }


protected:
    using TTransacation = std::pair<const std::uint8_t*, size_t>;
    std::queue<TTransacation> BusTransactions;

private:

    TTransactionCompletedHandler m_completedTransaction;
};

} // namespace Testing::Spi