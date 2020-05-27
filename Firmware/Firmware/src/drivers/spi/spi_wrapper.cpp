#include "spi_wrapper.hpp"
#include "pca10040.h"
#include "CallbackConnector.hpp"

#include <cassert>
#include <array>

#include "MetaUtils.hpp"

namespace Interface::Spi
{

SpiBus::SpiBus(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
        ,   std::uint32_t _pRegister
        ,   std::uint8_t _driverInstance
    )
    :   m_isTransactionCompleted{ true }
    ,   m_spiHandle{  reinterpret_cast<NRF_SPIM_Type*>(_pRegister), _driverInstance }
{

    // using TInstanceEnum = std::underlying_type_t< SpiInstance >;
    // TInstanceEnum instanceId = static_cast<TInstanceEnum>( _spiInstance );
    // NRFX_SPIM0_INST_IDX;

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
    Meta::UnuseVar( _pContext );

    if( _pEvent->type == NRFX_SPIM_EVENT_DONE )
    {
        if( !m_transactionsQueue.empty() )
        {

            auto& frontItem = m_transactionsQueue.front();

            if( frontItem.repeatsCount != 0 )
            {
                --frontItem.repeatsCount;
                frontItem.transactionAction();
                return;
            }

            if( frontItem.afterTransaction )
                frontItem.afterTransaction();

            m_transactionsQueue.pop();
            m_isTransactionCompleted = true;
            onTransactionCompleted.emit();

            runQueue();
        }
    }
}

std::uint16_t SpiBus::getDmaBufferSize()
{
    return SpiBus::DmaArray.size();
}

void SpiBus::addTransaction( Transaction&& _item )
{
    m_transactionsQueue.push( std::move( _item ) );
}

void SpiBus::runQueue()
{
    assert(m_isTransactionCompleted);
    if( !m_transactionsQueue.empty() && m_isTransactionCompleted )
    {
        assert( m_transactionsQueue.front().transactionAction );

        if( m_transactionsQueue.front().beforeTransaction )
            m_transactionsQueue.front().beforeTransaction();

        m_transactionsQueue.front().transactionAction();
    }
}

size_t SpiBus::getQueueSize()const
{
    return m_transactionsQueue.size();
}

void SpiBus::sendData( std::uint8_t _data )
{
    constexpr std::uint8_t transactionSize = 1;

    while( m_isTransactionCompleted )
    {        
        SpiBus::DmaArray[0] = _data;
        performTransaction( transactionSize );
    }
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

void SpiBus::sendChunk( const std::uint8_t* _pBuffer, const size_t _bufferSize )
{
    m_isTransactionCompleted = false;

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

void SpiBus::receiveChunk( std::uint8_t* _pBuffer, const size_t _bufferSize )
{
    m_isTransactionCompleted = false;

    nrfx_spim_xfer_desc_t xferDesc =
        NRFX_SPIM_XFER_RX(
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

SpiBus::DmaBufferType& SpiBus::getDmaBuffer()
{
    return DmaArray;
}

};
