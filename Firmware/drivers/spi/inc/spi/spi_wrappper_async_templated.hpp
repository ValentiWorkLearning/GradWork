#pragma once


#include <memory>
#include <atomic>
#include <coroutine>
#include <optional>
#include <cstdint>

#include <etl/vector.h>
#include <utils/CoroUtils.hpp>
#include <utils/Noncopyable.hpp>

namespace Interface::SpiTemplated
{


template<typename SpiBackendImpl>
class SpiBus
    : private Utils::noncopyable
{

public:

    SpiBus()noexcept
    {
        m_backendImpl.setTransactionCompletedHandler(
            [this] { transmitCompleted(); }
        );
    }
    ~SpiBus() = default;

public:

    static constexpr std::uint16_t DmaBufferSize = 255;
    using DmaBufferType = etl::vector<std::uint8_t, DmaBufferSize>;

    constexpr std::uint16_t getDmaBufferSize() noexcept
    {
        return DmaBufferSize;
    }

    constexpr DmaBufferType& getDmaBufferTransmit() noexcept
    {
        return DmaArrayTransmit;
    }

    void transmitBuffer(
        const std::uint8_t* _pBuffer
        , std::uint16_t _pBufferSize
        , void* _pUserData
        , bool restoreInSpiCtx
    )noexcept
    {
        m_coroHandle = std::coroutine_handle<>::from_address(_pUserData);

        const size_t TransferBufferSize = _pBufferSize;
        const size_t FullDmaTransactionsCount =
            TransferBufferSize / DmaBufferSize;
        const size_t ChunkedTransactionsBufSize =
            TransferBufferSize % DmaBufferSize;
        const bool ComputeChunkOffsetWithDma = FullDmaTransactionsCount >= 1;

        TransactionContext newContext
        {
                .restoreInSpiCtx = restoreInSpiCtx
            ,   .computeChunkOffsetWithDma = ComputeChunkOffsetWithDma
            ,   .pDataToTransmit = _pBuffer
            ,   .fullDmaTransactionsCount = FullDmaTransactionsCount
            ,   .chunkedTransactionBufSize = ChunkedTransactionsBufSize
            ,   .completedTransactionsCount = 0
        };

        m_transmitContext = newContext;

        if (FullDmaTransactionsCount)
        {
            --m_transmitContext->fullDmaTransactionsCount;
            m_backendImpl.sendChunk(
                _pBuffer
                , DmaBufferSize
            );
        }
        else {
            m_transmitContext->chunkedTransactionBufSize = 0;
            m_backendImpl.sendChunk(
                _pBuffer
                , _pBufferSize
            );
        }
    }

private:

    void transmitCompleted()noexcept
    {
        const bool isAllDmaTransactionsProceeded =
            m_transmitContext->fullDmaTransactionsCount == 0;
        const bool isAllChunckedTransactionsCompleted =
            m_transmitContext->chunkedTransactionBufSize == 0;

        if (!isAllDmaTransactionsProceeded)
        {
            --m_transmitContext->fullDmaTransactionsCount;

            m_backendImpl.sendChunk(
                m_transmitContext->pDataToTransmit + getTransitionOffset()
                , DmaBufferSize
            );
        }
        else if (!isAllChunckedTransactionsCompleted)
        {
            const size_t transmissionOffset = m_transmitContext->computeChunkOffsetWithDma
                ? DmaBufferSize
                * getTransitionOffset() : 0;

            const size_t TransmitBufferSize =
                m_transmitContext->chunkedTransactionBufSize;
            m_transmitContext->chunkedTransactionBufSize = 0;

            m_backendImpl.sendChunk(
                m_transmitContext->pDataToTransmit + transmissionOffset
                , TransmitBufferSize
            );
        }
        else {
            if (m_transmitContext->restoreInSpiCtx) {
                m_coroHandle.resume();
            }
            else {
                CoroUtils::CoroQueueMainLoop::GetInstance().pushToLater(m_coroHandle);
            }
        }
    }

private:
    std::size_t getTransitionOffset() noexcept
    {
        return m_transmitContext->completedTransactionsCount++;
    }

private:
    SpiBackendImpl m_backendImpl;
    std::coroutine_handle<> m_coroHandle;

    struct TransactionContext
    {
        bool restoreInSpiCtx = false;
        bool computeChunkOffsetWithDma = false;
        const std::uint8_t* pDataToTransmit = nullptr;
        size_t fullDmaTransactionsCount = 0;
        size_t chunkedTransactionBufSize = 0;
        size_t completedTransactionsCount = 0;
    };

    std::optional<TransactionContext> m_transmitContext;
    DmaBufferType DmaArrayTransmit;
    DmaBufferType DmaArrayReceive;
};

}