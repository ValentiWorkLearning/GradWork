#pragma once

#include <etl/vector.h>

#include <memory>
#include <atomic>
#include <coroutine>
#include <optional>
#include <cstdint>

#include <utils/CoroUtils.hpp>

namespace Interface::Spi
{

namespace SpiInstance
{
    struct M1;
    struct M2;
};

class GetCoroHandleKey
{
    friend class SpiBusAsync;
    friend class SpiAsyncBackendImpl;
private:
    GetCoroHandleKey() {}
    GetCoroHandleKey(const GetCoroHandleKey&) = default;
    GetCoroHandleKey& operator=(const GetCoroHandleKey&) = delete;
};

class SpiBusAsync
{

public:

    explicit SpiBusAsync(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
        ,   std::uint32_t _pRegister
        ,   std::uint8_t _driverInstance
    );

    ~SpiBusAsync();

public:

    static constexpr std::uint16_t DmaBufferSize = 255;
    using DmaBufferType = etl::vector<std::uint8_t,DmaBufferSize>;

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
        ,   std::uint16_t _pBufferSize
        ,   void* _pUserData
        ,   bool restoreInSpiCtx
    )noexcept;

    void transmitCompleted()noexcept;

    std::coroutine_handle<>
    getCoroutineHandle(const GetCoroHandleKey& _coroHandleKey)noexcept;

private:
    std::size_t getTransitionOffset() noexcept;

private:
    class SpiAsyncBackendImpl;
    std::unique_ptr<SpiAsyncBackendImpl> m_pSpiBackendImpl;

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

template< typename TSpiInstance >
std::unique_ptr<SpiBusAsync> createSpiBusAsync();


} // namespace Interface::Spi