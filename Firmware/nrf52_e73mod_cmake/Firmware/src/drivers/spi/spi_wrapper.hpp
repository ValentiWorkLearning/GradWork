#pragma once

#include<memory>
#include "nrfx_spim.h"
#include "bsp.h"

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
        static constexpr std::uint8_t DataCommandPin = SPIM0_DC_PIN;
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
        ,   std::uint8_t _dataCommandPin
    );

    ~SpiBus() = default;

public:

    void beginTransaction( );

    void endTransaction();

    bool sendData( std::uint8_t _data );

private:

    static constexpr std::uint8_t SlaveSelectDuration = 20;

    void spimEventHandler(
            nrfx_spim_evt_t const* _pEvent
        ,   void* _pContext
    );

private:
    nrfx_spim_t m_spiHandle;
};

template< typename TSpiInstance >
std::unique_ptr<SpiBus> createSpiBus()
{
    return std::make_unique<SpiBus>(
            TSpiInstance::ClockPin
        ,   TSpiInstance::MisoPin
        ,   TSpiInstance::MosiPin
        ,   TSpiInstance::SlaveSelectPin
        ,   TSpiInstance::DataCommandPin
    );
}

} // namespace Interface
