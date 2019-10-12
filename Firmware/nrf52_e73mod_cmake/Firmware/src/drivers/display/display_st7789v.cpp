#include "display_st7789v.hpp"
#include "display_st7789v_constants.hpp"

#include "spi/spi_wrapper.hpp"

// Based on Adafruit's implementation: https://github.com/adafruit/Adafruit-ST7735-Library/

namespace
{
    namespace DisplayReg = DisplayDriver::St7789vRegisters;
    constexpr std::int16_t InitSequenceSt7789[] =
    {                                                   // Init commands for 7789 screens
            9                                           //  9 commands in list:
        ,   DisplayReg::SWRESET,   DisplayReg::DELAY    //  1: Software reset, no args, w/delay
        ,   150                                         //     ~150 ms delay
        ,   DisplayReg::SLPOUT ,   DisplayReg::DELAY    //  2: Out of sleep mode, no args, w/delay
        ,   10                                          //      10 ms delay
        ,   DisplayReg::COLMOD , 1+DisplayReg::DELAY    //  3: Set color mode, 1 arg + delay:
        ,   0x55                                        //      16-bit color
        ,   10                                          //     10 ms delay
        ,   DisplayReg::MADCTL , 1                      //  4: Mem access ctrl (directions), 1 arg:
        ,   0x08                                        //     Row/col addr, bottom-top refresh
        ,   DisplayReg::CASET  , 4                      //  5: Column addr set, 4 args, no delay:
        ,   0x00
        ,   0                                           //     XSTART = 0
        ,   0
        ,   240                                         //     XEND = 240
        ,   DisplayReg::RASET  , 4                      //  6: Row addr set, 4 args, no delay:
        ,   0x00
        ,   0                                           //     YSTART = 0
        ,   320>>8
        ,   320&0xFF                                    //     YEND = 320
        ,   DisplayReg::INVON  ,   DisplayReg::DELAY    //  7: hack
        ,   10
        ,   DisplayReg::NORON  ,   DisplayReg::DELAY    //  8: Normal display on, no args, w/delay
        ,   10                                          //     10 ms delay
        ,   DisplayReg::DISPON ,   DisplayReg::DELAY    //  9: Main screen turn on, no args, delay
        ,   10                                          //    10 ms delay
    };
};

namespace DisplayDriver
{

constexpr St7789V::St7789V( Interface::Spi::SpiBus* _pBus )
    :   m_pBusPtr{ _pBus }
{
    //Just dummy action
    for( auto item : InitSequenceSt7789 )
        int a = item++;

    initDisplay();
}

void
St7789V::initDisplay()
{
    sendCommand( DisplayReg::SWRESET );
    sendCommand( DisplayReg::SLPOUT );
    sendCommand( DisplayReg::COLMOD, 0x55 );
    sendCommand( DisplayReg::MADCTL, 0x08 );
    sendCommand( DisplayReg::CASET, 0x00,0,0,240 );
    sendCommand( DisplayReg::RASET, 0x00, 0, 320>>8, 320&0xFF );
    sendCommand( DisplayReg::INVON );
    sendCommand( DisplayReg::NORON );
    sendCommand( DisplayReg::DISPON );
}

template<typename>
void St7789V::sendCommand(
        std::uint16_t _command
    ,   bool _withPostDelay
)
{
    m_pBusPtr->sendData( _command );
}

template< typename ... Args >
void St7789V::sendCommand(
        std::uint16_t _command
    ,   bool _withPostDelay
    ,   Args... _commandArgs
    )
{
    m_pBusPtr->sendData( _command );
    (m_pBusPtr->sendData( _commandArgs ), ...);
}

std::unique_ptr<St7789V>
createDisplayDriver()
{
    return std::make_unique<St7789V>( nullptr );
}

};