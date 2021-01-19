#include "inc/display/display_coro_compact_gc9a01.hpp"

namespace {
   
constexpr std::size_t CommandsSize = 328;
constexpr std::size_t CommandsTransactionsCount = 59;
static constexpr auto Commands = std::array<std::uint8_t, CommandsSize>
{
    /***Cmd****Argc****delay****argv*****************************/
        0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14

    ,   0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14
    ,   0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14

    ,   0xFE,   0,      0
    ,   0xEF,   0,      0

    ,   0x84,   1,      0,      0x40
    ,   0x85,   1,      0,      0xF1
    ,   0x86,   1,      0,      0x98
    ,   0x87,   1,      0,      0x28
    ,   0x88,   1,      0,      0x0A
    ,   0x89,   1,      0,      0x21

    ,   0x8A,   1,      0,      0x00
    ,   0x8B,   1,      0,      0x80
    ,   0x8C,   1,      0,      0x01
    ,   0x8D,   1,      0,      0x00
    ,   0x8E,   1,      0,      0xDF
    ,   0x8F,   1,      0,      0x52

    ,   0xB6,   1,      0,      0x20

    ,   0x36,   1,      0,      0x48

    ,   0x3A,   1,      0,      0x05

    ,   0x90,   4,      0,      0x08,0x08,0x08,0x08

    ,   0xBD,   1,      0,      0x06
    ,   0xA6,   1,      0,      0x74
    ,   0xBF,   1,      0,      0x1C
    ,   0xA7,   1,      0,      0x45
    ,   0xA9,   1,      0,      0xBB
    ,   0xB8,   1,      0,      0x63
    ,   0xE8,   1,      0,      0x34

    ,   0xFF,   3,      0,      0x60, 0x01,0x04

    ,   0x74,   7,      0,      0x10,0x75,0x80,0x00,0x00,0x4E,0x00
    ,   0xC3,   5,      0,      0x14,0xC4,0x14,0xC9,0x25

    ,   0xBE,   1,      0,      0x11
    ,   0xBC,   1,      0,      0x00
    ,   0xE1,   2,      0,      0x10,0x0e

    ,   0xDF,   3,      0,      0x21,0x0c,0x02

    ,   0xED,   2,      0,      0x1B,0x0B

    ,   0xAE,   5,      0,      0x77,0xCB,0x02,0xCD,0x63

    ,   0x70,   9,      0,      0x07,0x09,0x04,0x0e,0x0f, 0x09,0x07,0x08,0x03
    ,   0xf0,   6,      0,      0x45,0x09,0x08,0x08,0x26,0x2a
    ,   0xf1,   6,      0,      0x43,0x70,0x72,0x36,0x37,0x6f
    ,   0xf2,   6,      0,      0x45,0x09,0x08,0x08,0x26,0x2a
    ,   0xf3,   6,      0,      0x43,0x70,0x72,0x36,0x37,0x6f

    ,   0x62,   12,     0,      0x18,0x0d,0x71,0xED,0x70,0x70,0x18,0x0F,0x71,0xEF,0x70,0x70
    ,   0x63,   12,     0,      0x18,0x11,0x71,0xf1,0x70,0x70,0x18,0x13,0x71,0xf3,0x70,0x70
    ,   0x64,   7,      0,      0x28,0x29,0xF1,0x01,0xf1,0x00,0x07
    ,   0x66,   10,     0,      0x3c,0x00,0xCD,0x67,0x45,0x45,0x10,0x00,0x00,0x00
    ,   0x67,   10,     0,      0x00,0x3c,0x00,0x00,0x00,0x01,0x54,0x10,0x32,0x98
    ,   0x74,   7,      0,      0x10,0x85,0x80,0x00,0x00,0x4e,0x00

    ,   0x98,   2,      0,      0x3e,0x07

    ,   0x35,   0,      0
    ,   0x21,   0,      0

    ,   0x11,   0,      120
    ,   0x29,   0,      0
};
}

namespace DisplayDriver
{

GC9A01Compact::GC9A01Compact(std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr, std::uint16_t _width, std::uint16_t _height) noexcept
    : BaseSpiDisplayCoroutine(
        std::move(_busPtr)
        , _width
        , _height
    )
{
    initDisplay();
}
void GC9A01Compact::fillRectangle(
    std::uint16_t _x,
    std::uint16_t _y,
    std::uint16_t _width,
    std::uint16_t _height,
    IDisplayDriver::TColor* _colorToFill
) noexcept
{
    const std::uint16_t DisplayHeight = BaseSpiDisplayCoroutine::getHeight();
    const std::uint16_t DisplayWidth = BaseSpiDisplayCoroutine::getWidth();

    const bool isCoordsValid{ !((_x >= DisplayWidth) || (_y >= DisplayHeight)) };

    if (isCoordsValid)
    {
        if (_width >= DisplayWidth) _width = DisplayWidth - _x;
        if (_height >= DisplayHeight) _height = DisplayHeight - _y;

        const size_t BytesSizeX = (_width - _x + 1);
        const size_t BytesSizeY = (_height - _y + 1);
        const size_t BytesSquare = BytesSizeX * BytesSizeY;
        const size_t TransferBufferSize = (BytesSquare * sizeof(IDisplayDriver::TColor));

        co_await m_displayInitialized;
        co_await setAddrWindow(_x, _y, _width, _height);

        static constexpr std::uint8_t RamWriteCmd{0x29};

        co_await sendCommandImpl(&RamWriteCmd);  //LCD_WriteCMD(GRAMWR);

        setDcPin();
        co_await sendChunk(reinterpret_cast<const std::uint8_t*>(_colorToFill), TransferBufferSize);
        resetDcPin();

        LOG_DEBUG_ENDL("Draw something");
        onRectArreaFilled.emit();
    }
}

void GC9A01Compact::initDisplay() noexcept
{
    size_t CommandCount = CommandsTransactionsCount;
    const std::uint8_t* pBuffer = Commands.data();
    while(CommandCount--)
    {
        const std::uint8_t* Command = pBuffer++;
        const std::uint8_t NumArgs = *pBuffer++;
        const std::uint8_t Delay = *pBuffer++;

        co_await BaseSpiDisplayCoroutine::sendCommandImpl(Command);
        if (NumArgs) {
            co_await BaseSpiDisplayCoroutine::sendChunk(pBuffer++, NumArgs);
            pBuffer+=(NumArgs - 1);
        }

        if(Delay)
            Delay::waitFor(Delay);
    }
    m_displayInitialized.set();
}

CoroUtils::VoidTask
GC9A01Compact::setAddrWindow(
    std::uint16_t _x,
    std::uint16_t _y,
    std::uint16_t _width,
    std::uint16_t _height
) noexcept
{
        // TODO be careful here;
    std::uint16_t width = _width - _x;
    std::uint16_t height = _height - _y;

    std::uint16_t correctedX = _x;
    std::uint16_t correctedY = _y;

    uint32_t xa = ((uint32_t)correctedX << 16) | ( correctedX + width);// (_x+_width-1);
    int32_t ya = ((uint32_t)correctedY << 16) | ( correctedY +  height); //(_y+_height-1); 

    static std::array xAxisCommand =
        std::array{
                static_cast<std::uint8_t>( 0x2a )
            ,   static_cast<std::uint8_t>( xa >> 24 )
            ,   static_cast<std::uint8_t>( xa >> 16 )
            ,   static_cast<std::uint8_t>( xa >> 8 )
            ,   static_cast<std::uint8_t>( xa )
        };
    static std::array yAxisCommand =
        std::array{
                static_cast<std::uint8_t>( 0x2b )
            ,   static_cast<std::uint8_t>( ya >> 24 )
            ,   static_cast<std::uint8_t>( ya >> 16 )
            ,   static_cast<std::uint8_t>( ya >> 8 )
            ,   static_cast<std::uint8_t>( ya )
        };

    co_await CoroUtils::when_all_sequence(
            sendCommand(xAxisCommand.data(), xAxisCommand.size())
        ,   sendCommand(yAxisCommand.data(), yAxisCommand.size())
    );
}

std::unique_ptr<GC9A01Compact> createDisplayDriverCompactCoroBasedGC9A01(
    std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr,
    std::uint16_t _width,
    std::uint16_t _height
) noexcept
{
    return std::make_unique<GC9A01Compact>(
        std::move(_busPtr),
        _width,
        _height
    );
}

}
