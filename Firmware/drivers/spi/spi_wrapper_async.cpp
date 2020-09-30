#include "inc/spi/spi_wrapper_async.hpp"

#include "utils/MetaUtils.hpp"

#include "pca10040.h"

#include "nrfx_spim.h"

#include <coroutine>

namespace Interface::Spi
{

namespace SpiInstance
{
    struct M1
    {
        static constexpr std::uint8_t ClockPin = SPIM1_SCK_PIN;
        static constexpr std::uint8_t MisoPin = SPIM1_MISO_PIN;
        static constexpr std::uint8_t MosiPin = SPIM1_MOSI_PIN;
        static constexpr std::uint8_t SlaveSelectPin = SPIM1_SS_PIN;

        static constexpr std::uint32_t Register = NRF_SPIM1_BASE;
        static constexpr uint8_t DriverInstance = NRFX_SPIM1_INST_IDX;
    };

    struct M2
    {
        static constexpr std::uint8_t ClockPin = SPIM2_SCK_PIN;
        static constexpr std::uint8_t MisoPin = SPIM2_MISO_PIN;
        static constexpr std::uint8_t MosiPin = SPIM2_MOSI_PIN;
        static constexpr std::uint8_t SlaveSelectPin = SPIM2_SS_PIN;

        static constexpr std::uint32_t Register = NRF_SPIM2_BASE;
        static constexpr uint8_t DriverInstance = NRFX_SPIM2_INST_IDX;
    };

}; // namespace SpiInstance

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
        :   m_spiHandle{  reinterpret_cast<NRF_SPIM_Type*>(_pRegister), _driverInstance }
        ,   m_pSpiBus{ _pSpiBusHal }
    {
        nrfx_spim_config_t spiConfig{};

        spiConfig.sck_pin        = _clockPin;
        spiConfig.mosi_pin       = _mosiPin;
        spiConfig.miso_pin       = _misoPin;
        spiConfig.ss_pin         = _chipSelectPin;
        spiConfig.ss_active_high = false;
        spiConfig.irq_priority   = NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY;
        spiConfig.orc            = 0xFF;
        spiConfig.frequency      = NRF_SPIM_FREQ_8M;
        spiConfig.mode           = NRF_SPIM_MODE_0;
        spiConfig.bit_order      = NRF_SPIM_BIT_ORDER_MSB_FIRST;

        APP_ERROR_CHECK(
            nrfx_spim_init(
                    &m_spiHandle
                ,   &spiConfig
                ,   spimEventHandler
                ,   this
            )
        );
    }

public:

    void sendChunk(
            const std::uint8_t* _pBuffer
        ,   const size_t _bufferSize
    )noexcept
    {
        nrfx_spim_xfer_desc_t xferDesc =
            NRFX_SPIM_XFER_TX(
                    _pBuffer
                ,   _bufferSize
            );

        nrfx_err_t transmissionError = nrfx_spim_xfer(
                &m_spiHandle
            ,   &xferDesc
            ,   0
        );

        APP_ERROR_CHECK( transmissionError );
    }

private:

    static void spimEventHandler(
            nrfx_spim_evt_t const* _pEvent
        ,   void* _pContext
    )noexcept
    {
        Meta::UnuseVar( _pContext );
        if( _pEvent->type == NRFX_SPIM_EVENT_DONE )
        {
            auto pThis = reinterpret_cast<SpiBusAsync::SpiAsyncBackendImpl*>( _pContext );
            pThis->m_pSpiBus->transmitCompleted();
        }
    }

public:
    nrfx_spim_t m_spiHandle;
    SpiBusAsync* m_pSpiBus;
};



SpiBusAsync::SpiBusAsync(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
        ,   std::uint32_t _pRegister
        ,   std::uint8_t _driverInstance
    )
    :   m_pSpiBackendImpl{
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
        std::uint8_t* _pBuffer
    ,   std::uint16_t _pBufferSize
    ,   void* _pUserData
)
{
    m_coroHandle = std::coroutine_handle<>::from_address(_pUserData);

    const size_t TransferBufferSize = _pBufferSize;

    m_transmitContext.pDataToTransmit = _pBuffer;

    m_transmitContext.fullDmaTransactionsCount =
        TransferBufferSize / Interface::Spi::SpiBusAsync::DmaBufferSize;
    m_transmitContext.chunkedTransactionsCount =
        TransferBufferSize % Interface::Spi::SpiBusAsync::DmaBufferSize;

    m_transmitContext.completedTransactionsCount = 0;
    m_transmitContext.computeChunkOffsetWithDma =
        m_transmitContext.fullDmaTransactionsCount >= 1;

    if(m_transmitContext.fullDmaTransactionsCount > 0)
    {
        --m_transmitContext.fullDmaTransactionsCount;
        m_pSpiBackendImpl->sendChunk(
                _pBuffer
            ,   Interface::Spi::SpiBusAsync::DmaBufferSize
        );
    }
    else{
        m_pSpiBackendImpl->sendChunk(
                _pBuffer
            ,   _pBufferSize
        );
    }
}

void
SpiBusAsync::transmitCompleted()
{
    const bool isAllDmaTransactionsProceeded =
        m_transmitContext.fullDmaTransactionsCount != 0;

    if( !isAllDmaTransactionsProceeded )
    {
        --m_transmitContext.fullDmaTransactionsCount;

        m_pSpiBackendImpl->sendChunk(
                m_transmitContext.pDataToTransmit + getTransitionOffset()
            ,   Interface::Spi::SpiBusAsync::DmaBufferSize
        );
    }
    else if(m_transmitContext.chunkedTransactionsCount != 0)
    {
        const size_t transmissionOffset = m_transmitContext.computeChunkOffsetWithDma
            ?       Interface::Spi::SpiBusAsync::DmaBufferSize
                *   getTransitionOffset() : 0;

        m_pSpiBackendImpl->sendChunk(
                m_transmitContext.pDataToTransmit + transmissionOffset
            ,   m_transmitContext.chunkedTransactionsCount
        );
    }
    else{
        m_coroHandle.resume();
    }
}

std::uint32_t
SpiBusAsync::getTransitionOffset() noexcept
{
    return m_transmitContext.completedTransactionsCount++;
}

template< typename TSpiInstance >
std::unique_ptr<SpiBusAsync> createSpiBusAsync()
{
    return std::make_unique<SpiBusAsync>(
            TSpiInstance::ClockPin
        ,   TSpiInstance::MisoPin
        ,   TSpiInstance::MosiPin
        ,   TSpiInstance::SlaveSelectPin
        ,   TSpiInstance::Register
        ,   TSpiInstance::DriverInstance
    );
}

template class std::unique_ptr<SpiBusAsync>
createSpiBusAsync<SpiInstance::M1>();

template class std::unique_ptr<SpiBusAsync>
createSpiBusAsync<SpiInstance::M2>();


} // namespace Interface::Spi