#include "inc/spi/spi_wrapper.hpp"

#include "utils/CallbackConnector.hpp"
#include "utils/MetaUtils.hpp"

#include "pca10040.h"

#include "nrfx_spim.h"

#include <cassert>
#include <array>

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
};

class SpiBus::SpiBackendImpl
{
    public:

    SpiBackendImpl(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
        ,   std::uint32_t _pRegister
        ,   std::uint8_t _driverInstance
        ,   SpiBus* _pSpiBus
    )
        :   m_spiHandle{  reinterpret_cast<NRF_SPIM_Type*>(_pRegister), _driverInstance }
        ,   m_pSpiBus{ _pSpiBus }
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

    void performTransaction( uint16_t _dataSize )
    {
        nrfx_spim_xfer_desc_t xferDesc =
            NRFX_SPIM_XFER_TX(
                m_pSpiBus->getDmaBufferTransmit().data()
            ,   _dataSize
        );

        nrfx_err_t transmissionError = nrfx_spim_xfer(
                &m_spiHandle
            ,   &xferDesc
            ,   0
        );
        APP_ERROR_CHECK( transmissionError );
    }

    void sendChunk( const std::uint8_t* _pBuffer, const size_t _bufferSize )
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


    void xferChunk(
                const std::uint8_t* _pTransmitBuffer
            ,   const size_t _transmitBufferSize
            ,   std::uint8_t* _pReceiveBuffer
            ,   const size_t _receiveBufferSize
        )
    {

        nrfx_spim_xfer_desc_t xferDesc =
            NRFX_SPIM_XFER_TRX(
                    _pTransmitBuffer
                ,   _transmitBufferSize
                ,   _pReceiveBuffer
                ,   _receiveBufferSize
            );

        nrfx_err_t transmissionError = nrfx_spim_xfer(
                &m_spiHandle
            ,   &xferDesc
            ,   0
        );

        APP_ERROR_CHECK( transmissionError );
    }

    void receiveAsync(
                const size_t _bytesCount
            ,   std::uint8_t* _pReceiveBuffer
            ,   const size_t _receiveBufferSize
        )
    {
        //assert( _bytesCount <= _receiveBufferSize );

        nrfx_spim_xfer_desc_t receiveAsyncDesc =
            NRFX_SPIM_XFER_RX(
                    _pReceiveBuffer
                ,   _bytesCount
            );

        nrfx_err_t transmissionError = nrfx_spim_xfer(
                &m_spiHandle
            ,   &receiveAsyncDesc
            ,   0
        );

        APP_ERROR_CHECK( transmissionError );
    }
    private:

    static void spimEventHandler(
            nrfx_spim_evt_t const* _pEvent
        ,   void* _pContext
    )
    {
        Meta::UnuseVar( _pContext );
        if( _pEvent->type == NRFX_SPIM_EVENT_DONE )
        {
            auto pThis = reinterpret_cast<SpiBus::SpiBackendImpl*>( _pContext );
            pThis->m_pSpiBus->handleEvent( SpiBus::TCompletedEvent::TransactionCompleted );
        }
    }

    public:
    nrfx_spim_t m_spiHandle;
    SpiBus* m_pSpiBus;
};

SpiBus::SpiBus(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
        ,   std::uint32_t _pRegister
        ,   std::uint8_t _driverInstance
    )
    :   m_isTransactionCompleted{ true }
    ,   m_completedTransitionsCount{}
    ,   m_pSpiBackendImpl{
            std::make_unique<SpiBackendImpl>(
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

SpiBus::~SpiBus() = default;

void
SpiBus::handleEvent( TCompletedEvent _eventToHandle )
{
    if( _eventToHandle == TCompletedEvent::TransactionCompleted )
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
    return SpiBus::DmaArrayTransmit.size();
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
        SpiBus::DmaArrayTransmit[0] = _data;
        performTransaction( transactionSize );
    }
}

void SpiBus::performTransaction( uint16_t _dataSize )
{
    m_isTransactionCompleted = false;
    m_pSpiBackendImpl->performTransaction( _dataSize );
}

void SpiBus::sendChunk( const std::uint8_t* _pBuffer, const size_t _bufferSize )
{
    m_isTransactionCompleted = false;
    m_pSpiBackendImpl->sendChunk( _pBuffer,_bufferSize );
}

void SpiBus::xferChunk(
        const std::uint8_t* _pTransmitBuffer
    ,   const size_t _transmitBufferSize
)
{
    m_isTransactionCompleted = false;
    m_pSpiBackendImpl->xferChunk(
            _pTransmitBuffer
        ,   _transmitBufferSize
        ,   DmaArrayReceive.data()
        ,   DmaArrayReceive.size()
    );
}

void
SpiBus::receiveAsync( const size_t _bytesCount )
{
    m_isTransactionCompleted = false;

    m_pSpiBackendImpl->receiveAsync(
            _bytesCount
        ,   DmaArrayReceive.data()
        ,   DmaArrayReceive.size()
    );
}

SpiBus::DmaBufferType&
SpiBus::getDmaBufferTransmit()
{
    return DmaArrayTransmit;
}

SpiBus::DmaBufferType&
SpiBus::getDmaBufferReceive()
{
    return DmaArrayReceive;
}

void
SpiBus::addXferTransaction( TransactionDescriptor&& _deskcriptor )
{
    TransactionDescriptor localDescriptor{std::move( _deskcriptor )};

    std::visit(
            [ this,&localDescriptor ](auto&& _tTransactionData)
            {
                using TTransactionData = std::decay_t<decltype( _tTransactionData )>;

                Transaction transactionInternalImpl;

                if constexpr (std::is_same_v<TTransactionData, std::uint8_t>)
                {

                    transactionInternalImpl.beforeTransaction = localDescriptor.beforeTransaction;
                    transactionInternalImpl.afterTransaction = localDescriptor.afterTransaction;

                    transactionInternalImpl.transactionAction =
                        [this,_tTransactionData]
                        {
                            m_isTransactionCompleted = false;

                            SpiBus::DmaArrayTransmit[0] = _tTransactionData;

                            constexpr std::uint8_t transactionSize = 1;
                            m_pSpiBackendImpl->performTransaction( transactionSize );
                        };

                    m_transactionsQueue.push( std::move( transactionInternalImpl ) );
                }
                else if constexpr (std::is_same_v<TTransactionData, TransactionDescriptor::DataSequence>)
                {
                    setupBlockTransactionInternal(
                            localDescriptor.beforeTransaction
                        ,   localDescriptor.afterTransaction
                        ,   _tTransactionData
                    );
                }
            }
        ,   localDescriptor.transactionData
    );
}

void
SpiBus::setupBlockTransactionInternal(
        std::function<void()> beforeTransaction
    ,   std::function<void()> afterTransaction
    ,   const TransactionDescriptor::DataSequence& dataSequence
)
{

    m_completedTransitionsCount = 0;

    const size_t TransferBufferSize = dataSequence.blockSize;
    const size_t FullDmaTransactionsCount =  TransferBufferSize  / Interface::Spi::SpiBus::DmaBufferSize;
    const size_t ChunkedTransactionsCount = TransferBufferSize  % Interface::Spi::SpiBus::DmaBufferSize;

    const std::uint8_t* pDataBlock = dataSequence.dataBlock;

    if( FullDmaTransactionsCount > 0 )
    {
        Interface::Spi::Transaction fullTransaction{};
        fullTransaction.beforeTransaction = beforeTransaction;
        fullTransaction.transactionAction =
            [this, pDataBlock]
            {
                std::uint32_t addrOffset = Interface::Spi::SpiBus::DmaBufferSize
                            *   getTransitionOffset();

                    this->sendChunk(
                        pDataBlock + addrOffset
                    ,   Interface::Spi::SpiBus::DmaBufferSize
                );
            };

        if( FullDmaTransactionsCount > 1 )
            fullTransaction.repeatsCount = FullDmaTransactionsCount - 1;

        if( ChunkedTransactionsCount == 0 )
            fullTransaction.afterTransaction = afterTransaction;

        this->addTransaction( std::move( fullTransaction ) );
    }

    if( ChunkedTransactionsCount > 0 )
    {
        Interface::Spi::Transaction chunkTransmission{};
        chunkTransmission.beforeTransaction = beforeTransaction;

        chunkTransmission.transactionAction =
            [this, pDataBlock,ChunkedTransactionsCount ,FullDmaTransactionsCount ]
            {
                const size_t transmissionOffset = FullDmaTransactionsCount >= 1
                    ?   DmaBufferSize * getTransitionOffset() : 0;

                this->sendChunk(
                        pDataBlock + transmissionOffset
                    ,   ChunkedTransactionsCount
                );
            };
            chunkTransmission.afterTransaction = afterTransaction;

        this->addTransaction( std::move( chunkTransmission ) );
    }
}

std::uint32_t
SpiBus::getTransitionOffset()
{
    return m_completedTransitionsCount++;
}

template< typename TSpiInstance >
std::unique_ptr<SpiBus> createSpiBus()
{
    return std::make_unique<SpiBus>(
            TSpiInstance::ClockPin
        ,   TSpiInstance::MisoPin
        ,   TSpiInstance::MosiPin
        ,   TSpiInstance::SlaveSelectPin
        ,   TSpiInstance::Register
        ,   TSpiInstance::DriverInstance
    );
}

template class std::unique_ptr<SpiBus> createSpiBus<SpiInstance::M1>();
template class std::unique_ptr<SpiBus> createSpiBus<SpiInstance::M2>();

};
