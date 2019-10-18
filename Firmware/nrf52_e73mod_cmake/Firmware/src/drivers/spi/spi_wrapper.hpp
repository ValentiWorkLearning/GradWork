#pragma once

#include "nrfx_spim.h"

#include "transaction_item.hpp"

#include <queue>
#include <memory>
#include "utils/nod.hpp"

namespace Interface::Spi
{

class TransactionListener;

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

    static constexpr std::uint16_t DmaArraySize = 480;

    std::uint16_t getDmaBufferSize();

    template< typename FillerFunction >
    void fillDmaArray( FillerFunction _functor );

public:

    bool sendData( std::uint8_t _data );

    template< typename TSequenceContainter>
    bool sendChunk( const TSequenceContainter& _arrayToTransmit );

    nod::unsafe_signal<void()> onTransactionComplete;

public:

    void addTransaction( Transaction && _item );

    void runQueue();

private:

    void spimEventHandler(
            nrfx_spim_evt_t const* _pEvent
        ,   void* _pContext
    );

    void initGpio();

    void performTransaction( uint16_t _dataSize );

private:

    volatile bool m_isTransactionCompleted;
    nrfx_spim_t m_spiHandle;

    static std::array<std::uint8_t,DmaArraySize> DmaArray;
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
bool SpiBus::sendChunk( const TSequenceContainter& _arrayToTransmit )
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
    return true;
}

template< typename FillerFunction >
void SpiBus::fillDmaArray( FillerFunction _functor )
{
    for( size_t i{}; i<SpiBus::DmaArraySize; ++i )
        SpiBus::DmaArray[i] = _functor( i );
}

} // namespace Interface
