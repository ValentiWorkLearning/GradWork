#include "inc/display/display_gc9a01.hpp"

#include <array>

namespace HorizontalOrientation
{
    enum class THorizontal
    {
            kUseHorizontalOne
        ,   kUseHorizontalTwo
        ,   kUseHorizontalThree
    };

    constexpr THorizontal CurrentChoise = THorizontal::kUseHorizontalTwo;
}

namespace DisplayDriver
{

GC9A01::GC9A01(
            Interface::Spi::SpiBus&& _busPtr
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
}

GC9A01::~GC9A01()= default;

void
GC9A01::initDisplay()
{
    BaseSpiDisplay::resetResetPin();
    Delay::waitFor( 100 );
    BaseSpiDisplay::setResetPin();

    sendCommand(0xFE);
    sendCommand(0xEF);
    sendCommand(0xEB,0x14);

    sendCommand(0xFE);
    sendCommand(0xEF);

    sendCommand(0x84,0x40);
    sendCommand(0x85,0xF1);
    sendCommand(0x86,0x98);
    sendCommand(0x87,0x28);
    sendCommand(0x88,0x0A);
    sendCommand(0x89,0x21);

    sendCommand(0x8A,0x00);
    sendCommand(0x8B,0x80);
    sendCommand(0x8C,0x01);
    sendCommand(0x8D,0x00);
    sendCommand(0x8E,0xDF);
    sendCommand(0x8F,0x52);

    sendCommand(0xB6,0x20);

    sendCommand(0x36,0x48);

    sendCommand(0x3A,0x05);

    sendCommand(0x90,0x08,0x08,0x08,0x08);

    sendCommand(0xBD,0x06);
    sendCommand(0xA6,0x74);
    sendCommand(0xBF,0x1C);
    sendCommand(0xA7,0x45);
    sendCommand(0xA9,0xBB);
    sendCommand(0xB8,0x63);
    sendCommand(0xE8,0x34);

    sendCommand(0xFF,0x60, 0x01,0x04);

    sendCommand(0x74, 0x10,0x75,0x80,0x00,0x00,0x4E,0x00);
    BaseSpiDisplay::getSpiBus()->runQueue();
    Delay::waitFor( 120 );
    sendCommand(0xC3,0x14,0xC4,0x14,0xC9,0x25 );

    sendCommand(0xBE,0x11);
    sendCommand(0xBC,0x00);
    sendCommand(0xE1,0x10,0x0e);

    sendCommand(0xDF,0x21,0x0c,0x02);

    sendCommand(0xED, 0x1B,0x0B );

    sendCommand(0xAE, 0x77,0xCB,0x02,0xCD,0x63 );

    sendCommand(0x70,0x07,0x09,0x04,0x0e,0x0f, 0x09,0x07,0x08,0x03);
    sendCommand(0xf0,0x45,0x09,0x08,0x08,0x26,0x2a);
    sendCommand(0xf1,0x43,0x70,0x72,0x36,0x37,0x6f);
    sendCommand(0xf2,0x45,0x09,0x08,0x08,0x26,0x2a);
    sendCommand(0xf3,0x43,0x70,0x72,0x36,0x37,0x6f);

    sendCommand(0x62,0x18,0x0d,0x71,0xED,0x70,0x70,0x18,0x0F,0x71,0xEF,0x70,0x70);
    sendCommand(0x63,0x18,0x11,0x71,0xf1,0x70,0x70,0x18,0x13,0x71,0xf3,0x70,0x70);
    sendCommand(0x64,0x28,0x29,0xF1,0x01,0xf1,0x00,0x07);
    sendCommand(0x66,0x3c,0x00,0xCD,0x67,0x45,0x45,0x10,0x00,0x00,0x00);
    sendCommand(0x67,0x00,0x3c,0x00,0x00,0x00,0x01,0x54,0x10,0x32,0x98);
    sendCommand(0x74,0x10,0x85,0x80,0x00,0x00,0x4e,0x00);

    sendCommand(0x98,0x3e,0x07);

    sendCommand(0x35);
    sendCommand(0x21);

    sendCommand(0x11);  //Sleep out	
    BaseSpiDisplay::getSpiBus()->runQueue();

    Delay::waitFor( 120 );
    sendCommand( 0x29 );
    BaseSpiDisplay::getSpiBus()->runQueue();
}

void GC9A01::turnOn()
{
}

void GC9A01::turnOff()
{
}

void GC9A01::fillRectangle(
        std::uint16_t _x
    ,   std::uint16_t _y
    ,   std::uint16_t _width
    ,   std::uint16_t _height
    ,   IDisplayDriver::TColor* _colorToFill
)
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

    sendCommand(0x2c);  //LCD_WriteCMD(GRAMWR);

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

void GC9A01::setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
)
{
    // TODO be careful here;
    std::uint16_t width = _width - _x;
    std::uint16_t height = _height - _y;

    std::uint16_t correctedX = _x;
    std::uint16_t correctedY = _y;

    uint32_t xa = ((uint32_t)correctedX << 16) | ( correctedX + width);// (_x+_width-1);
    int32_t ya = ((uint32_t)correctedY << 16) | ( correctedY +  height); //(_y+_height-1); 

    sendCommand(
            0x2a
        ,   static_cast<std::uint8_t>( xa >> 24 )
        ,   static_cast<std::uint8_t>( xa >> 16 )
        ,   static_cast<std::uint8_t>( xa >> 8 )
        ,   static_cast<std::uint8_t>( xa )
    );

    sendCommand(
            0x2b
        ,   static_cast<std::uint8_t>( ya >> 24 )
        ,   static_cast<std::uint8_t>( ya >> 16 )
        ,   static_cast<std::uint8_t>( ya >> 8 )
        ,   static_cast<std::uint8_t>( ya )
    );
}

std::unique_ptr<GC9A01>
createDisplayDriverGC9A01(
        Interface::Spi::SpiBus&& _bus
    ,   std::uint16_t _width
    ,   std::uint16_t _height
)
{
    return std::make_unique<GC9A01>(
            std::move( _bus )
        ,   _width
        ,   _height
    );
}

};
