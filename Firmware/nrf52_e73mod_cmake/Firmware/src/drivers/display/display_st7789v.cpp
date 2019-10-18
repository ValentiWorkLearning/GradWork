#include "display_st7789v.hpp"
#include "display_st7789v_constants.hpp"

#include "spi/transaction_item.hpp"
#include "spi/spi_wrapper.hpp"

#include "nrf_delay.h"

#include <array>

// Based on Adafruit's implementation: https://github.com/adafruit/Adafruit-ST7735-Library/
// Thanks eax.me : https://github.com/afiskon/stm32-st7735/blob/master/st7735/st7735.c

namespace DisplayReg = DisplayDriver::St7789vRegisters;

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
    initGpio();
    initDisplay();
    initColumnRow( _width, _height );
}

void
St7789V::initDisplay()
{
    nrf_gpio_pin_clear( DISP_RST );
    nrf_delay_ms( 100 );
    nrf_gpio_pin_set( DISP_RST );

    sendCommand(    DisplayReg::SWRESET    );
    nrf_delay_ms( 150 );
    sendCommand(    DisplayReg::SLPOUT     );
    sendCommand(    DisplayReg::COLMOD     , 0x55   );
    sendCommand(    DisplayReg::MADCTL     , 0x08   );
    sendCommand(    DisplayReg::CASET      , 0x00,0,0,240 );
    sendCommand(    DisplayReg::RASET      , 0x00, 0, 320>>8, 320&0xFF );
    sendCommand(    DisplayReg::INVON      );
    sendCommand(    DisplayReg::NORON      );
    sendCommand(    DisplayReg::DISPON     );
    sendCommand(    DisplayReg::MADCTL     , 0xC0   );

    m_pBusPtr->runQueue();
}

void St7789V::sendCommand(
        std::uint8_t _command
)
{
    Interface::Spi::Transaction commandTransaction;

    commandTransaction.beforeTransaction =
        [ this ]
        {
            m_pBusPtr->resetDcPin();
        };
    
    commandTransaction.transactionAction =
        [ this, _command ]
        {
            m_pBusPtr->sendData( _command );
        };

    commandTransaction.afterTransaction =
        [ this ]
        {
            m_pBusPtr->setDcPin();
        };
    
    m_pBusPtr->addTransaction( std::move( commandTransaction ) );

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

    Interface::Spi::Transaction chunkTransaction;

    chunkTransaction.beforeTransaction =
        [ this ]
        {
            setDcPin();
        };
    
    chunkTransaction.transactionAction =
        [ this, chunk ]
        {
            m_pBusPtr->sendChunk( chunk );
        };

    chunkTransaction.afterTransaction =
        [ this ]
        {
            resetDcPin();
        };
    
    m_pBusPtr->addTransaction( std::move( chunkTransaction ) );
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
        m_rowStart = 110;
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

    sendCommand( DisplayReg::RAMWR );

    m_pBusPtr->fillDmaArray(
        [ localColor ]( size_t index )
        {
            std::uint8_t value = ( index % 2 ) == 0 ? localColor >> 8 : localColor & 0xFF;
            return value;
        }
    );

    m_pBusPtr->runQueue();
    m_pBusPtr->runRepeatedSend( _height * 2 );

    // // // get _height
    // // // get _width

    // for(_y = _height; _y > 0; _y--)
    // {
    //     sendChunk( localColor >> 8 );
    //     sendChunk( localColor & 0xFF );
    // }
    // m_pBusPtr->runQueue();
}

void St7789V::setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
)
{
    _x +=m_columnStart;
    _y +=m_rowStart;

    uint32_t xa = ((uint32_t)_x << 16) | (_x+_width-1);
    uint32_t ya = ((uint32_t)_y << 16) | (_y+_height-1); 

    sendCommand(
            DisplayReg::CASET
        ,   static_cast<std::uint8_t>( xa >> 24 )
        ,   static_cast<std::uint8_t>( xa >> 16 )
        ,   static_cast<std::uint8_t>( xa >> 8 )
        ,   static_cast<std::uint8_t>( xa )
    );

    sendCommand(
            DisplayReg::RASET
        ,   static_cast<std::uint8_t>( ya >> 24 )
        ,   static_cast<std::uint8_t>( ya >> 16 )
        ,   static_cast<std::uint8_t>( ya >> 8 )
        ,   static_cast<std::uint8_t>( ya )
    );
    
    m_pBusPtr->runQueue();
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
    m_pBusPtr->runQueue();
}

void St7789V::initGpio()
{
    nrf_gpio_cfg_output( DISP_RST );
    nrf_gpio_cfg_output( DISP_DC_PIN );
}

void St7789V::resetDcPin()
{
    nrf_gpio_pin_clear( DISP_DC_PIN );
}
    
void St7789V::setDcPin()
{
    nrf_gpio_pin_set( DISP_DC_PIN );
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