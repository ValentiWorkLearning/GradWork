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

#include "utils/MetaUtils.hpp"

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
    {
    }

public:

    void sendChunk(
        const std::uint8_t* _pBuffer
        , const size_t _bufferSize
    )noexcept
    {
        std::thread dmaThread = std::thread(
            [this, _pBuffer,_bufferSize]
            {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(500ms);

                std::cout << "TRANSMIT SOME DATA:" << ' ';

                for (size_t i{}; i<_bufferSize; ++i)
                {
                    std::cout << std::hex << _pBuffer[i] << ' ';
                }
                std::cout << std::endl;
                //std::cout << "TRANSMIT SOME DATA" << "THREAD:" << std::this_thread::get_id() << std::endl;
                
                auto suspendedCoroutineHandle = m_pSpiBus->getCoroutineHandle(GetCoroHandleKey{});
                suspendedCoroutineHandle.resume();
            }
            );
        dmaThread.detach();
    }

private:
    SpiBusAsync* m_pSpiBus;
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
    std::uint8_t * _pBuffer
    , std::uint16_t _pBufferSize
    , void* _pUserData
)
{
    m_coroHandle = stdcoro::coroutine_handle<>::from_address(_pUserData);

    const size_t TransferBufferSize = _pBufferSize;

    m_transmitContext.pDataToTransmit = _pBuffer;

    m_transmitContext.fullDmaTransactionsCount =
        TransferBufferSize / Interface::Spi::SpiBusAsync::DmaBufferSize;
    m_transmitContext.chunkedTransactionsCount =
        TransferBufferSize % Interface::Spi::SpiBusAsync::DmaBufferSize;

    m_transmitContext.completedTransactionsCount = 0;
    m_transmitContext.computeChunkOffsetWithDma =
        m_transmitContext.fullDmaTransactionsCount >= 1;

    if (m_transmitContext.fullDmaTransactionsCount > 0)
    {
        --m_transmitContext.fullDmaTransactionsCount;
        m_pSpiBackendImpl->sendChunk(
            _pBuffer
            , Interface::Spi::SpiBusAsync::DmaBufferSize
        );
    }
    else {
        m_pSpiBackendImpl->sendChunk(
            _pBuffer
            , _pBufferSize
        );
    }
}

void
SpiBusAsync::transmitCompleted()
{
    const bool isAllDmaTransactionsProceeded =
        m_transmitContext.fullDmaTransactionsCount != 0;

    if (!isAllDmaTransactionsProceeded)
    {
        --m_transmitContext.fullDmaTransactionsCount;

        m_pSpiBackendImpl->sendChunk(
            m_transmitContext.pDataToTransmit + getTransitionOffset()
            , Interface::Spi::SpiBusAsync::DmaBufferSize
        );
    }
    else if (m_transmitContext.chunkedTransactionsCount != 0)
    {
        const size_t transmissionOffset = m_transmitContext.computeChunkOffsetWithDma
            ? Interface::Spi::SpiBusAsync::DmaBufferSize
            * getTransitionOffset() : 0;

        m_pSpiBackendImpl->sendChunk(
            m_transmitContext.pDataToTransmit + transmissionOffset
            , m_transmitContext.chunkedTransactionsCount
        );
    }
    else {
        m_coroHandle.resume();
    }
}

std::uint32_t
SpiBusAsync::getTransitionOffset() noexcept
{
    return m_transmitContext.completedTransactionsCount++;
}

stdcoro::coroutine_handle<>
SpiBusAsync::getCoroutineHandle(const GetCoroHandleKey& _coroHandleKey)
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