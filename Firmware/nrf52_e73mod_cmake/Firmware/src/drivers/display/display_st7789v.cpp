#include "display_st7789v.hpp"
#include "display_st7789v_constants.hpp"

#include "spi/spi_wrapper.hpp"

#include "nrf_delay.h"

#include <array>

// Based on Adafruit's implementation: https://github.com/adafruit/Adafruit-ST7735-Library/
// Thanks eax.me : https://github.com/afiskon/stm32-st7735/blob/master/st7735/st7735.c

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

St7789V::St7789V(
            Interface::Spi::SpiBus* _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )
    :   m_width{ _width }
    ,   m_height { _height }
    ,   m_pBusPtr{ _busPtr }
{
    //Just dummy action
    for( auto item : InitSequenceSt7789 )
        int a = item++;

    initDisplay();
    initColumnRow( _width, _height );
}

void
St7789V::initDisplay()
{
    sendCommand(    DisplayReg::SWRESET    );
    nrf_delay_ms( 150 );
    sendCommand(    DisplayReg::SLPOUT     );
    nrf_delay_ms( 10 );
    sendCommand(    DisplayReg::COLMOD     , 0x55   );
    nrf_delay_ms( 10 );
    sendCommand(    DisplayReg::MADCTL     , 0x08   );
    sendCommand(    DisplayReg::CASET      , 0x00,0,0,240 );
    sendCommand(    DisplayReg::RASET      , 0x00, 0, 320>>8, 320&0xFF );
    sendCommand(    DisplayReg::INVON      );
    nrf_delay_ms( 10 );
    sendCommand(    DisplayReg::NORON      );
    nrf_delay_ms( 10 );
    sendCommand(    DisplayReg::DISPON     );
    nrf_delay_ms( 10 );
}

void St7789V::sendCommand(
        std::uint8_t _command
)
{
    m_pBusPtr->resetDcPin();
    m_pBusPtr->sendData( _command );
    m_pBusPtr->setDcPin();
}

template< typename ... Args >
void St7789V::sendCommand(
        std::uint8_t _command
    ,   Args... _commandArgs
    )
{
    sendCommand( _command );
    sendChunk( _commandArgs... );
}

template< typename ... Args >
void St7789V::sendChunk(
        Args... _chunkArgs
)
{
    std::array chunk = { _chunkArgs... };
    
    m_pBusPtr->setDcPin();
    m_pBusPtr->sendChunk( chunk );
}

void St7789V::initColumnRow(
        std::uint16_t _width
    ,   std::uint16_t _height
)
{
    if(
            _width == DisplayDriver::St7789v::Disp208_240::Width
        &&  _height == DisplayDriver::St7789v::Disp208_240::Height
    )
    {
        m_columnStart = 0;
        m_rowStart = 80;        
    }
    else if( 
            _width == DisplayDriver::St7789v::Disp240_320::Width
        &&  _height == DisplayDriver::St7789v::Disp240_320::Height
    )
    {
        m_columnStart = 0;
        m_rowStart = 0;
    }
}

void St7789V::turnOn()
{
    sendCommand( DisplayReg::DISPON );
}

void St7789V::turnOff()
{
    sendCommand( DisplayReg::DISPOFF );
}

void St7789V::fillColor( DisplayDriver::Colors _color )
{
    fillRectangle(
            0
        ,   0
        ,   m_width
        ,   m_height
        ,   _color
    );
}


void St7789V::fillRectangle(
        std::uint16_t _x
    ,   std::uint16_t _y
    ,   std::uint16_t _width
    ,   std::uint16_t _height
    ,   DisplayDriver::Colors _color
)
{
    if((_x >= m_width) || (_y >= m_height )) return;
    if((_x + _width - 1) >= m_width) _width = m_width - _x;
    if((_y + _height - 1) >= m_height) _height = m_height - _y;

    using TColor = std::underlying_type<DisplayDriver::Colors>::type;

    TColor localColor { static_cast<TColor>( _color ) };

    setAddrWindow(
            _x
        ,   _y
        ,   _x + _width - 1
        ,   _y + _height - 1
    );

    for(_y = _height; _y > 0; _y--)
    {
        for(_x = _width; _x > 0; _x--)
        {
            sendChunk(
                    localColor >> 8
                ,   localColor & 0xFF
            );
        }
    }
}

void St7789V::setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
)
{
    constexpr std::uint8_t ST7789_XSTART = 0;
    constexpr std::uint8_t ST7789_YSTART = 0;

    sendCommand(
            DisplayReg::CASET
        ,   0x00
        ,   _x + ST7789_XSTART
        ,   0x00
        ,   _width + ST7789_XSTART
    );

    sendCommand(
            DisplayReg::RASET
        ,   0x00
        ,   _y + ST7789_YSTART
        ,   0x00
        ,   _height + ST7789_YSTART
    );
}

void St7789V::drawPixel(
        std::uint16_t _x
    ,   std::uint16_t _y
    ,   DisplayDriver::Colors _color
)
{
    setAddrWindow( _x, _y, _x+1, _y+1 );

    using TColor = std::underlying_type<DisplayDriver::Colors>::type;

    TColor localColor { static_cast<TColor>( _color ) };

    sendChunk(
            localColor >> 8
        ,   localColor & 0xFF
    );
}

std::unique_ptr<St7789V>
createDisplayDriver(
        Interface::Spi::SpiBus* _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
)
{
    return std::make_unique<St7789V>(
            _busPtr
        ,   _width
        ,   _height
    );
}

};