#include "inc/display/display_st7789v.hpp"
#include "display_st7789v_constants.hpp"

#include <array>

namespace DisplayReg = DisplayDriver::St7789vRegisters;

namespace DisplayDriver
{

St7789V::St7789V(
            std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )
    :   BaseSpiDisplay(
                std::move( _busPtr )
            ,   _width
            ,   _height
        )
{
    initDisplay();
    initColumnRow( _width, _height );
}

St7789V::~St7789V()noexcept= default;

void
St7789V::initDisplay()noexcept
{
    BaseSpiDisplay::resetResetPin();
    Delay::waitFor( 100 );
    BaseSpiDisplay::setResetPin();

    sendCommand(    DisplayReg::SWRESET    );
    Delay::waitFor( 150 );
    sendCommand(    DisplayReg::SLPOUT     );
    sendCommand(    DisplayReg::COLMOD     , 0x55   );
    sendCommand(    DisplayReg::MADCTL     , 0x08   );
    sendCommand(    DisplayReg::CASET      , 0x00,0,0,240 );
    sendCommand(    DisplayReg::RASET      , 0x00, 0, 320>>8, 320&0xFF );
    sendCommand(    DisplayReg::INVON      );
    sendCommand(    DisplayReg::NORON      );
    sendCommand(    DisplayReg::DISPON     );
    sendCommand(    DisplayReg::MADCTL     , 0xC0   ); // 0xC0 for inverted orientation

    BaseSpiDisplay::getSpiBus()->runQueue();
}

void St7789V::initColumnRow(
        std::uint16_t _width
    ,   std::uint16_t _height
)noexcept
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
        m_rowStart = 40;
    }
}

void St7789V::turnOn()noexcept
{
    sendCommand( DisplayReg::DISPON );
}

void St7789V::turnOff()noexcept
{
    sendCommand( DisplayReg::DISPOFF );
}

void St7789V::fillRectangle(
        std::uint16_t _x
    ,   std::uint16_t _y
    ,   std::uint16_t _width
    ,   std::uint16_t _height
    ,   IDisplayDriver::TColor* _colorToFill
)noexcept
{
    const std::uint16_t DisplayHeight = BaseSpiDisplay::getHeight();
    const std::uint16_t DisplayWidth = BaseSpiDisplay::getWidth();

    if( (_x >= DisplayWidth) || (_y >= DisplayHeight )) return;
    if( _width >= DisplayWidth) _width = DisplayWidth - _x;
    if( _height>= DisplayHeight) _height = DisplayHeight - _y;

    const size_t BytesSizeX = ( _width - _x + 1 );
    const size_t BytesSizeY = ( _height - _y + 1);
    const size_t BytesSquare = BytesSizeX *  BytesSizeY;
    const size_t TransferBufferSize =  ( BytesSquare* sizeof ( IDisplayDriver::TColor ) );

    setAddrWindow(
            _x
        ,   _y
        ,   _width
        ,   _height
    );

    sendCommand( DisplayReg::RAMWR );

    Interface::Spi::TransactionDescriptor blockSetup
        {
                [ this ]{ setDcPin();}
            ,   [ this ]{ onRectArreaFilled.emit(); resetDcPin(); }
            ,   Interface::Spi::TransactionDescriptor::DataSequence{
                        reinterpret_cast<const std::uint8_t*>( _colorToFill )
                    ,   TransferBufferSize
                }
        };

    BaseSpiDisplay::getSpiBus()->addXferTransaction( std::move( blockSetup ) );
    BaseSpiDisplay::getSpiBus()->runQueue();
}

void St7789V::setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
)noexcept
{
    // TODO be careful here;
    std::uint16_t width = _width - _x;
    std::uint16_t height = _height - _y;

    std::uint16_t correctedX = _x + m_columnStart;
    std::uint16_t correctedY = _y + m_rowStart;

    uint32_t xa = ((uint32_t)correctedX << 16) | ( correctedX + width);// (_x+_width-1);
    int32_t ya = ((uint32_t)correctedY << 16) | ( correctedY +  height); //(_y+_height-1); 

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
    
}

std::unique_ptr<St7789V>
createDisplayDriverSt7789V(
        std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
)noexcept
{
    return std::make_unique<St7789V>(
            std::move( _busPtr )
        ,   _width
        ,   _height
    );
}

};
