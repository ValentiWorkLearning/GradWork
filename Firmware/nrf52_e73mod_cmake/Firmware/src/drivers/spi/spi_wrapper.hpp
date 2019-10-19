#pragma once

#include "nrfx_spim.h"
#include "pca10040.h"

#include "SimpleSignal.hpp"

#include "transaction_item.hpp"

#include <queue>
#include <memory>

namespace Interface::Spi
{

namespace SpiInstance
{
    struct M0
    {
        static constexpr std::uint8_t ClockPin = SPIM0_SCK_PIN;
        static constexpr std::uint8_t MisoPin = SPIM0_MISO_PIN;
        static constexpr std::uint8_t MosiPin = SPIM0_MOSI_PIN;
        static constexpr std::uint8_t SlaveSelectPin = SPIM0_SS_PIN;
    };
};

class SpiBus
{

public:

    explicit SpiBus(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
    );

    ~SpiBus() = default;

public:

    static constexpr std::uint16_t DmaBufferSize = 240;
    using DmaBufferType = std::vector<std::uint8_t>;

    std::uint16_t getDmaBufferSize();

public:

    void sendData( std::uint8_t _data );

    template< typename TSequenceContainter>
    void sendChunk( const TSequenceContainter& _arrayToTransmit );

    void sendFullDmaArray();

    DmaBufferType& getDmaBuffer();

    Simple::Signal<void()> onTransactionStarted;
    Simple::Signal<void()> onTransactionCompleted;

public:

    void addTransaction( Transaction && _item );

    void runQueue();

private:

    void spimEventHandler(
            nrfx_spim_evt_t const* _pEvent
        ,   void* _pContext
    );

    void performTransaction( uint16_t _dataSize );

private:

    volatile bool m_isTransactionCompleted;
    nrfx_spim_t m_spiHandle;

    static DmaBufferType DmaArray;
    std::queue<Transaction> m_transactionsQueue;
};

template< typename TSpiInstance >
std::unique_ptr<SpiBus> createSpiBus()
{
    return std::make_unique<SpiBus>(
            TSpiInstance::ClockPin
        ,   TSpiInstance::MisoPin
        ,   TSpiInstance::MosiPin
        ,   TSpiInstance::SlaveSelectPin
    );
}

template< typename TSequenceContainter>
void SpiBus::sendChunk( const TSequenceContainter& _arrayToTransmit )
{
    while( m_isTransactionCompleted )
    {
        std::copy(
                std::begin( _arrayToTransmit )
            ,   std::end( _arrayToTransmit )
            ,   std::begin( SpiBus::DmaArray )
        );
        performTransaction( _arrayToTransmit.size() );
    }
}

} // namespace Interface
