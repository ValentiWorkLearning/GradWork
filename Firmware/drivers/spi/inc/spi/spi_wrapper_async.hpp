#pragma once

#include <etl/vector.h>

#include <memory>
#include <atomic>

#ifdef WIN32
#include <experimental/coroutine>
namespace stdcoro = std::experimental;
#else
#include <coroutine>
namespace stdcoro = std;
#endif // WIN32


namespace Interface::Spi
{

namespace SpiInstance
{
    struct M1;
    struct M2;
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

    void transmitBuffer(
            std::uint8_t* _pBuffer
        ,   std::uint16_t _pBufferSize
        ,   void* _pUserData
    );

    void transmitCompleted();

private:
    std::uint32_t getTransitionOffset() noexcept;

private:
    class SpiAsyncBackendImpl;
    std::unique_ptr<SpiAsyncBackendImpl> m_pSpiBackendImpl;

    stdcoro::coroutine_handle<> m_coroHandle;

    struct TransactionContext
    {
        std::uint8_t* pDataToTransmit = nullptr;
        size_t fullDmaTransactionsCount = 0;
        size_t chunkedTransactionsCount = 0;
        size_t completedTransactionsCount = 0;
        bool computeChunkOffsetWithDma = false;
    };

    TransactionContext m_transmitContext;
    DmaBufferType DmaArrayTransmit;
    DmaBufferType DmaArrayReceive;
};

template< typename TSpiInstance >
std::unique_ptr<SpiBusAsync> createSpiBusAsync();


} // namespace Interface::Spi