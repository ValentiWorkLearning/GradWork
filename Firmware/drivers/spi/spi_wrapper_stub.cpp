#include "inc/spi/spi_wrapper_async.hpp"

#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cstdint>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <mutex>
#include <condition_variable>

#include "utils/MetaUtils.hpp"

#define USE_THREADING_ASYNC_BACKEND


namespace Interface::Spi
{

namespace SpiInstance
{
    struct M1
    {
        static constexpr std::uint8_t ClockPin = 0;
        static constexpr std::uint8_t MisoPin = 0;
        static constexpr std::uint8_t MosiPin = 0;
        static constexpr std::uint8_t SlaveSelectPin = 0;

        static constexpr std::uint32_t Register = 0;
        static constexpr uint8_t DriverInstance = 0;
    };

    struct M2
    {
        static constexpr std::uint8_t ClockPin = 0;
        static constexpr std::uint8_t MisoPin = 0;
        static constexpr std::uint8_t MosiPin = 0;
        static constexpr std::uint8_t SlaveSelectPin = 0;

        static constexpr std::uint32_t Register = 0;
        static constexpr uint8_t DriverInstance = 0;
    };
};

class SpiBusAsync::SpiAsyncBackendImpl
{

public:
    SpiAsyncBackendImpl(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
        ,   std::uint32_t _pRegister
        ,   std::uint8_t _driverInstance
        ,   SpiBusAsync* _pSpiBusHal
    )
        :   m_pSpiBus{ _pSpiBusHal }
        ,   m_newDataArrived{ false }
        ,   m_pDataBuffer{ nullptr }
        ,   m_bufferTransmitSize{}
        ,   m_processSpiTransactions{true}
    {
#ifdef  USE_THREADING_ASYNC_BACKEND

        m_dmaThread = std::make_unique<std::thread>(
            [this]
            {
                while (m_processSpiTransactions)
                {
                    if(m_newDataArrived)
                    {
                        using namespace std::chrono_literals;
                        //std::this_thread::sleep_for(1500ms);

                        std::cout << "TRANSMIT SOME DATA:" << ' ';

                        for (size_t i{}; i < m_bufferTransmitSize; ++i)
                        {
                            std::cout << std::hex << static_cast<std::int16_t>(m_pDataBuffer[i]) << ' ';
                        }
                        std::cout << std::endl;

                        m_newDataArrived.store(false);
                        m_pSpiBus->transmitCompleted();
                    }
                }
            }
       );
#endif  //  USE_THREADING_ASYNC_BACKEND
    }

    ~SpiAsyncBackendImpl()
    {
        m_processSpiTransactions.store(false);
        m_dmaThread->detach();
        m_dmaThread.reset();
    }

public:

    void sendChunk(
        const std::uint8_t* _pBuffer
        , const size_t _bufferSize
    )noexcept
    {
        m_bufferTransmitSize.store( _bufferSize );
        m_pDataBuffer.store( _pBuffer );
        m_newDataArrived.store( true, std::memory_order_release );

#ifndef USE_THREADING_ASYNC_BACKEND
        std::cout << "TRANSMIT SOME DATA:" << ' ';

        for ( size_t i{}; i < m_bufferTransmitSize; ++i )
        {
            std::cout << std::hex
                      << static_cast<std::int16_t>( m_pDataBuffer[i] ) << ' ';
        }
        std::cout << std::endl;

        m_newDataArrived.store( false );
        m_pSpiBus->transmitCompleted();
#endif
    }

private:
    SpiBusAsync* m_pSpiBus;

    std::atomic_bool m_newDataArrived;
    std::atomic_bool m_processSpiTransactions;
    std::atomic<const std::uint8_t*> m_pDataBuffer;
    std::atomic<size_t> m_bufferTransmitSize;

    std::unique_ptr<std::thread> m_dmaThread;
};



SpiBusAsync::SpiBusAsync(
    std::uint8_t _clockPin
    , std::uint8_t _misoPin
    , std::uint8_t _mosiPin
    , std::uint8_t _chipSelectPin
    , std::uint32_t _pRegister
    , std::uint8_t _driverInstance
)
    : m_pSpiBackendImpl{
            std::make_unique<SpiAsyncBackendImpl>(
                    _clockPin
                ,   _misoPin
                ,   _mosiPin
                ,   _chipSelectPin
                ,   _pRegister
                ,   _driverInstance
                ,   this
            )
}
{
}

SpiBusAsync::~SpiBusAsync() = default;

void
SpiBusAsync::transmitBuffer(
        const std::uint8_t * _pBuffer
    ,   std::uint16_t _pBufferSize
    ,   void* _pUserData
    , bool restoreInSpiCtx
) noexcept
{
    Meta::UnuseVar(restoreInSpiCtx);

    m_coroHandle = std::coroutine_handle<>::from_address(_pUserData);

    const size_t TransferBufferSize = _pBufferSize;
    const size_t FullDmaTransactionsCount =
        TransferBufferSize / Interface::Spi::SpiBusAsync::DmaBufferSize;
    const size_t ChunkedTransactionsBufSize =
        TransferBufferSize % Interface::Spi::SpiBusAsync::DmaBufferSize;
    const bool ComputeChunkOffsetWithDma = FullDmaTransactionsCount >= 1;

    TransactionContext newContext
    {
            .computeChunkOffsetWithDma = ComputeChunkOffsetWithDma
        ,   .pDataToTransmit = _pBuffer
        ,   .fullDmaTransactionsCount = FullDmaTransactionsCount
        ,   .chunkedTransactionBufSize = ChunkedTransactionsBufSize
        ,   .completedTransactionsCount = 0
    };

    m_transmitContext = newContext;

    if (FullDmaTransactionsCount)
    {
        --m_transmitContext->fullDmaTransactionsCount;
        m_pSpiBackendImpl->sendChunk(
            _pBuffer
            , Interface::Spi::SpiBusAsync::DmaBufferSize
        );
    }
    else {
        m_transmitContext->chunkedTransactionBufSize = 0;
        m_pSpiBackendImpl->sendChunk(
            _pBuffer
            , _pBufferSize
        );
    }
}

void
SpiBusAsync::transmitCompleted()noexcept
{
    const bool isAllDmaTransactionsProceeded =
        m_transmitContext->fullDmaTransactionsCount == 0;
    const bool isAllChunckedTransactionsCompleted =
        m_transmitContext->chunkedTransactionBufSize == 0;

    if (!isAllDmaTransactionsProceeded)
    {
        --m_transmitContext->fullDmaTransactionsCount;

        m_pSpiBackendImpl->sendChunk(
            m_transmitContext->pDataToTransmit + getTransitionOffset()
            , Interface::Spi::SpiBusAsync::DmaBufferSize
        );
    }
    else if (!isAllChunckedTransactionsCompleted)
    {
        const size_t transmissionOffset = m_transmitContext->computeChunkOffsetWithDma
            ? Interface::Spi::SpiBusAsync::DmaBufferSize
            * getTransitionOffset() : 0;

        const size_t TransmitBufferSize =
            m_transmitContext->chunkedTransactionBufSize;
        m_transmitContext->chunkedTransactionBufSize = 0;

        m_pSpiBackendImpl->sendChunk(
                m_transmitContext->pDataToTransmit + transmissionOffset
            ,   TransmitBufferSize
        );
    }
    else {
        CoroUtils::CoroQueueMainLoop::GetInstance().pushToLater(m_coroHandle);
    }
}

std::size_t
SpiBusAsync::getTransitionOffset() noexcept
{
    return m_transmitContext->completedTransactionsCount++;
}

std::coroutine_handle<>
SpiBusAsync::getCoroutineHandle(const GetCoroHandleKey& _coroHandleKey)noexcept
{
    Meta::UnuseVar(_coroHandleKey);
    return m_coroHandle;
}

template< typename TSpiInstance >
std::unique_ptr<SpiBusAsync> createSpiBusAsync()
{
    return std::make_unique<SpiBusAsync>(
        TSpiInstance::ClockPin
        , TSpiInstance::MisoPin
        , TSpiInstance::MosiPin
        , TSpiInstance::SlaveSelectPin
        , TSpiInstance::Register
        , TSpiInstance::DriverInstance
        );
}

template class std::unique_ptr<SpiBusAsync>
createSpiBusAsync<SpiInstance::M1>();

template class std::unique_ptr<SpiBusAsync>
createSpiBusAsync<SpiInstance::M2>();


} // namespace Interface::Spi