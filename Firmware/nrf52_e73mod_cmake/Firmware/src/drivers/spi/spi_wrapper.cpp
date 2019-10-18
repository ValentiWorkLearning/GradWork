#include "spi_wrapper.hpp"
#include "pca10040.h"
#include "CallbackConnector.hpp"

#include <array>

#define SPI_INSTANCE  0

namespace Interface::Spi
{

std::array<std::uint8_t,SpiBus::DmaArraySize>
SpiBus::DmaArray = {};

SpiBus::SpiBus(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
    )
    :   m_isTransactionCompleted{ true }
{

    // using TInstanceEnum = std::underlying_type_t< SpiInstance >;
    // TInstanceEnum instanceId = static_cast<TInstanceEnum>( _spiInstance );
    // NRFX_SPIM0_INST_IDX;

    initGpio();

    m_spiHandle = NRFX_SPIM_INSTANCE( SPI_INSTANCE );

    nrfx_spim_config_t spiConfig{};

    spiConfig.sck_pin        = SPIM0_SCK_PIN;
    spiConfig.mosi_pin       = SPIM0_MOSI_PIN;
    spiConfig.miso_pin       = SPIM0_MISO_PIN;
    spiConfig.ss_pin         = SPIM0_SS_PIN;
    spiConfig.ss_active_high = false;
    spiConfig.irq_priority   = NRFX_SPIM_DEFAULT_CONFIG_IRQ_PRIORITY;
    spiConfig.orc            = 0xFF;
    spiConfig.frequency      = NRF_SPIM_FREQ_8M;
    spiConfig.mode           = NRF_SPIM_MODE_0;
    spiConfig.bit_order      = NRF_SPIM_BIT_ORDER_MSB_FIRST;

     auto eventHandler = cbc::obtain_connector(
       [ this ]( nrfx_spim_evt_t const* _pEvent, void* _pContext )
       {
           spimEventHandler( _pEvent,_pContext );
       }
     );

    APP_ERROR_CHECK(
        nrfx_spim_init(
                &m_spiHandle
            ,   &spiConfig
            ,   eventHandler
            ,   nullptr
        )
    );

}

void SpiBus::spimEventHandler(
        nrfx_spim_evt_t const* _pEvent
    ,   void* _pContext
)
{
    if( _pEvent->type == NRFX_SPIM_EVENT_DONE )
    {
        m_isTransactionCompleted = true;

        onTransactionComplete();

        if( !m_transactionsQueue.empty() )
        {
            if( m_transactionsQueue.front().afterTransaction )
                m_transactionsQueue.front().afterTransaction();

            m_transactionsQueue.pop();

            runQueue();
        }
    }
}

void SpiBus::initGpio()
{
    nrf_gpio_cfg_output( SPIM0_DC_PIN );
}


std::uint16_t SpiBus::getDmaBufferSize()
{
    return SpiBus::DmaArray.size();
}

void SpiBus::addTransaction( Transaction && _item )
{
    m_transactionsQueue.push( std::move( _item ) );
}

void SpiBus::runQueue()
{
    if( !m_transactionsQueue.empty() && m_isTransactionCompleted )
    {
        if( m_transactionsQueue.front().beforeTransaction )
            m_transactionsQueue.front().beforeTransaction();

        m_transactionsQueue.front().transactionAction();
    }
}

bool SpiBus::sendData( std::uint8_t _data )
{
    constexpr std::uint8_t transactionSize = 1;

    while( m_isTransactionCompleted )
    {        
        SpiBus::DmaArray[0] = _data;
        performTransaction( transactionSize );
    }
    return true;
}

void SpiBus::performTransaction( uint16_t _dataSize )
{
    m_isTransactionCompleted = false;

    nrfx_spim_xfer_desc_t xferDesc =
        NRFX_SPIM_XFER_TX(
                SpiBus::DmaArray.data()
            ,   _dataSize
        );

    nrfx_err_t transmissionError = nrfx_spim_xfer(
            &m_spiHandle
        ,   &xferDesc
        ,   0
    );

    APP_ERROR_CHECK( transmissionError );
}

};