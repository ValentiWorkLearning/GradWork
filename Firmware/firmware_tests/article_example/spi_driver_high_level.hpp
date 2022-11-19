#pragma once
#include <array>
#include <atomic>
#include <cstdint>
#include <memory>
#include <optional>
#include <span>

#include "coroutine_utils.hpp"

template <typename SpiBackendImpl> class SpiBus
{

public:
    SpiBus() noexcept = default;
    ~SpiBus() = default;

public:
    static constexpr std::uint16_t DmaBufferSize = 255;
    using DmaBufferType = std::array<std::uint8_t, DmaBufferSize>;

    constexpr std::uint16_t getDmaBufferSize() noexcept
    {
        return DmaBufferSize;
    }

    constexpr DmaBufferType& getDmaBufferTransmit() noexcept
    {
        return DmaArrayTransmit;
    }

    constexpr DmaBufferType& getDmaBufferReceive() noexcept
    {
        return DmaArrayReceive;
    }

    void xferBuffer(
        std::span<const std::uint8_t> _transmitArray,
        std::span<std::uint8_t> _receiveArray,
        void* _pUserData,
        bool _restoreInSpiCtx)
    {
        m_backendImpl.setTransactionCompletedHandler([this] { transmitCompleted(); });

        m_coroHandle = stdcoro::coroutine_handle<>::from_address(_pUserData);

        TransactionContext newContext{
            .restoreInSpiCtx = _restoreInSpiCtx,
            .computeChunkOffsetWithDma = 0,
            .pDataToTransmit = _transmitArray.data(),
            .fullDmaTransactionsCount = 0,
            .chunkedTransactionBufSize = _transmitArray.size(),
            .completedTransactionsCount = 0};

        m_transmitContext = std::move(newContext);

        m_backendImpl.xferChunk(_transmitArray, _receiveArray);
    }

    void transmitBuffer(
        const std::uint8_t* _pBuffer,
        std::uint16_t _pBufferSize,
        void* _pUserData,
        bool _restoreInSpiCtx) noexcept
    {
        m_coroHandle = stdcoro::coroutine_handle<>::from_address(_pUserData);
        m_backendImpl.setTransactionCompletedHandler([this] { transmitCompleted(); });

        const size_t TransferBufferSize = _pBufferSize;
        const size_t FullDmaTransactionsCount = TransferBufferSize / DmaBufferSize;
        const size_t ChunkedTransactionsBufSize = TransferBufferSize % DmaBufferSize;
        const bool ComputeChunkOffsetWithDma = FullDmaTransactionsCount >= 1;

        TransactionContext newContext{
            .restoreInSpiCtx = _restoreInSpiCtx,
            .computeChunkOffsetWithDma = ComputeChunkOffsetWithDma,
            .pDataToTransmit = _pBuffer,
            .fullDmaTransactionsCount = FullDmaTransactionsCount,
            .chunkedTransactionBufSize = ChunkedTransactionsBufSize,
            .completedTransactionsCount = 0};

        m_transmitContext = std::move(newContext);

        if (FullDmaTransactionsCount)
        {
            --m_transmitContext.fullDmaTransactionsCount;
            m_backendImpl.sendChunk(_pBuffer, DmaBufferSize);
        }
        else
        {
            m_transmitContext.chunkedTransactionBufSize = 0;
            m_backendImpl.sendChunk(_pBuffer, _pBufferSize);
        }
    }

public:
    SpiBackendImpl& getBackendImpl() noexcept
    {
        return m_backendImpl;
    }

    const SpiBackendImpl& getBackendImpl() const noexcept
    {
        return m_backendImpl;
    }

private:
    void transmitCompleted() noexcept
    {
        const bool isAllDmaTransactionsProceeded = m_transmitContext.fullDmaTransactionsCount == 0;
        const bool isAllChunckedTransactionsCompleted =
            m_transmitContext.chunkedTransactionBufSize == 0;

        if (!isAllDmaTransactionsProceeded)
        {
            --m_transmitContext.fullDmaTransactionsCount;

            m_backendImpl.sendChunk(
                m_transmitContext.pDataToTransmit + DmaBufferSize * getTransitionOffset(),
                DmaBufferSize);
        }
        else if (!isAllChunckedTransactionsCompleted)
        {
            const size_t transmissionOffset = m_transmitContext.computeChunkOffsetWithDma
                                                  ? DmaBufferSize * getTransitionOffset()
                                                  : 0;

            const size_t TransmitBufferSize = m_transmitContext.chunkedTransactionBufSize;
            m_transmitContext.chunkedTransactionBufSize = 0;

            m_backendImpl.sendChunk(
                m_transmitContext.pDataToTransmit + transmissionOffset, TransmitBufferSize);
        }
        else
        {
            if (m_transmitContext.restoreInSpiCtx)
            {
                m_coroHandle.resume();
            }
            else
            {
                CoroUtils::CoroQueueMainLoop::GetInstance().pushToLater(m_coroHandle);
            }
        }
    }

private:
    std::size_t getTransitionOffset() noexcept
    {
        return ++m_transmitContext.completedTransactionsCount;
    }

private:
    SpiBackendImpl m_backendImpl;
    stdcoro::coroutine_handle<> m_coroHandle;

    struct TransactionContext
    {
        bool restoreInSpiCtx = false;
        bool computeChunkOffsetWithDma = false;
        const std::uint8_t* pDataToTransmit = nullptr;
        size_t fullDmaTransactionsCount = 0;
        size_t chunkedTransactionBufSize = 0;
        size_t completedTransactionsCount = 0;
    };

    TransactionContext m_transmitContext;
    DmaBufferType DmaArrayTransmit;
    DmaBufferType DmaArrayReceive;
};