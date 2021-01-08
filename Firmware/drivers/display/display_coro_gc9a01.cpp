#include "inc/display/display_coro_gc9a01.hpp"

#include "logger/logger_service.hpp"
#include <array>

namespace
{
template< std::uint8_t ... Command>
struct CommandDescriptor {};

template<std::uint8_t Command, std::uint8_t CommandDelay ,std::uint8_t ... CommandArgs>
struct CommandDescriptor< Command, CommandDelay, CommandArgs...>
{
    std::uint8_t commandDelay = CommandDelay;
    std::array<std::uint8_t,sizeof...(CommandArgs)+1> command{ Command,CommandArgs... };
};

template<std::uint8_t Command, std::uint8_t CommandDelay>
struct CommandDescriptor<Command, CommandDelay>
{
    std::uint8_t commandDelay = CommandDelay;
    std::array<std::uint8_t,1> command{ Command };
};

template<std::uint8_t Command>
struct CommandDescriptor<Command>
{
    std::uint8_t commandDelay = 0;
    std::array<std::uint8_t, 1> command{ Command };
};

constexpr std::uint8_t bitwiseResolutionConstant()
{
    return  320 >> 8;
}

inline constexpr std::uint8_t DefaultDelay = 0;

static constexpr std::tuple CommandsArray = {
        CommandDescriptor<0xFE>{}
    ,   CommandDescriptor<0xEF>{}
    ,   CommandDescriptor<0xEB,DefaultDelay, 0x14>{}
    ,   CommandDescriptor<0xFE>{}
    ,   CommandDescriptor<0xEF>{}
    ,   CommandDescriptor<0xEB,DefaultDelay, 0x14>{}
    ,   CommandDescriptor<0xFE>{}
    ,   CommandDescriptor<0xEF>{}
    ,   CommandDescriptor<0xEB,DefaultDelay,0x14>{}

    ,   CommandDescriptor<0xFE>{}
    ,   CommandDescriptor<0xEF>{}

    ,   CommandDescriptor<0x84,DefaultDelay,0x40>{}
    ,   CommandDescriptor<0x85,DefaultDelay,0xF1>{}
    ,   CommandDescriptor<0x86,DefaultDelay,0x98>{}
    ,   CommandDescriptor<0x87,DefaultDelay,0x28>{}
    ,   CommandDescriptor<0x88,DefaultDelay,0x0A>{}
    ,   CommandDescriptor<0x89,DefaultDelay,0x21>{}

    ,   CommandDescriptor<0x8A,DefaultDelay,0x00>{}
    ,   CommandDescriptor<0x8B,DefaultDelay,0x80>{}
    ,   CommandDescriptor<0x8C,DefaultDelay,0x01>{}
    ,   CommandDescriptor<0x8D,DefaultDelay,0x00>{}
    ,   CommandDescriptor<0x8E,DefaultDelay,0xDF>{}
    ,   CommandDescriptor<0x8F,DefaultDelay,0x52>{}

    ,   CommandDescriptor<0xB6,DefaultDelay,0x20>{}

    ,   CommandDescriptor<0x36,DefaultDelay,0x48>{}

    ,   CommandDescriptor<0x3A,DefaultDelay,0x05>{}

    ,   CommandDescriptor<0x90,DefaultDelay,0x08,0x08,0x08,0x08>{}

    ,   CommandDescriptor<0xBD,DefaultDelay,0x06>{}
    ,   CommandDescriptor<0xA6,DefaultDelay,0x74>{}
    ,   CommandDescriptor<0xBF,DefaultDelay,0x1C>{}
    ,   CommandDescriptor<0xA7,DefaultDelay,0x45>{}
    ,   CommandDescriptor<0xA9,DefaultDelay,0xBB>{}
    ,   CommandDescriptor<0xB8,DefaultDelay,0x63>{}
    ,   CommandDescriptor<0xE8,DefaultDelay,0x34>{}

    ,   CommandDescriptor<0xFF,DefaultDelay,0x60, 0x01,0x04>{}

    ,   CommandDescriptor<0x74,DefaultDelay,0x10,0x75,0x80,0x00,0x00,0x4E,0x00>{}
    ,   CommandDescriptor<0xC3,DefaultDelay,0x14,0xC4,0x14,0xC9,0x25>{}

    ,   CommandDescriptor<0xBE,DefaultDelay,0x11>{}
    ,   CommandDescriptor<0xBC,DefaultDelay,0x00>{}
    ,   CommandDescriptor<0xE1,DefaultDelay,0x10,0x0e>{}

    ,   CommandDescriptor<0xDF,DefaultDelay,0x21,0x0c,0x02>{}

    ,   CommandDescriptor<0xED,DefaultDelay,0x1B,0x0B>{}

    ,   CommandDescriptor<0xAE,DefaultDelay,0x77,0xCB,0x02,0xCD,0x63>{}

    ,   CommandDescriptor<0x70,DefaultDelay,0x07,0x09,0x04,0x0e,0x0f, 0x09,0x07,0x08,0x03>{}
    ,   CommandDescriptor<0xf0,DefaultDelay,0x45,0x09,0x08,0x08,0x26,0x2a>{}
    ,   CommandDescriptor<0xf1,DefaultDelay,0x43,0x70,0x72,0x36,0x37,0x6f>{}
    ,   CommandDescriptor<0xf2,DefaultDelay,0x45,0x09,0x08,0x08,0x26,0x2a>{}
    ,   CommandDescriptor<0xf3,DefaultDelay,0x43,0x70,0x72,0x36,0x37,0x6f>{}

    ,   CommandDescriptor<0x62,DefaultDelay,0x18,0x0d,0x71,0xED,0x70,0x70,0x18,0x0F,0x71,0xEF,0x70,0x70>{}
    ,   CommandDescriptor<0x63,DefaultDelay,0x18,0x11,0x71,0xf1,0x70,0x70,0x18,0x13,0x71,0xf3,0x70,0x70>{}
    ,   CommandDescriptor<0x64,DefaultDelay,0x28,0x29,0xF1,0x01,0xf1,0x00,0x07>{}
    ,   CommandDescriptor<0x66,DefaultDelay,0x3c,0x00,0xCD,0x67,0x45,0x45,0x10,0x00,0x00,0x00>{}
    ,   CommandDescriptor<0x67,DefaultDelay,0x00,0x3c,0x00,0x00,0x00,0x01,0x54,0x10,0x32,0x98>{}
    ,   CommandDescriptor<0x74,DefaultDelay,0x10,0x85,0x80,0x00,0x00,0x4e,0x00>{}

    ,   CommandDescriptor<0x98,DefaultDelay,0x3e,0x07>{}

    ,   CommandDescriptor<0x35>{}
    ,   CommandDescriptor<0x21>{}

    ,   CommandDescriptor<0x11>{}
    ,   CommandDescriptor<0x29>{}
};

}
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

GC9A01Coro::GC9A01Coro(
            std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    ) noexcept
    :   BaseSpiDisplayCoroutine(
                std::move( _busPtr )
            ,   _width
            ,   _height
        )
{
    initDisplay();
}

GC9A01Coro::~GC9A01Coro()noexcept= default;

void
GC9A01Coro::initDisplay()noexcept
{
    BaseSpiDisplayCoroutine::resetResetPin();
    Delay::waitFor( 100 );
    BaseSpiDisplayCoroutine::setResetPin();

    co_await launchInit(
        CommandsArray,
        std::make_integer_sequence<std::size_t, std::tuple_size<decltype(CommandsArray)>::value> {}
    );
    m_displayInitialized.set();
}

void GC9A01Coro::turnOn()noexcept
{
}

void GC9A01Coro::turnOff()noexcept
{
}

void GC9A01Coro::fillRectangle(
        std::uint16_t _x
    ,   std::uint16_t _y
    ,   std::uint16_t _width
    ,   std::uint16_t _height
    ,   IDisplayDriver::TColor* _colorToFill
)noexcept
{
    const std::uint16_t DisplayHeight = BaseSpiDisplayCoroutine::getHeight();
    const std::uint16_t DisplayWidth = BaseSpiDisplayCoroutine::getWidth();

    const bool isCoordsValid{ !( (_x >= DisplayWidth) || (_y >= DisplayHeight )) };

    if( isCoordsValid)
    {
        if( _width >= DisplayWidth) _width = DisplayWidth - _x;
        if( _height>= DisplayHeight) _height = DisplayHeight - _y;

        const size_t BytesSizeX = ( _width - _x + 1 );
        const size_t BytesSizeY = ( _height - _y + 1);
        const size_t BytesSquare = BytesSizeX *  BytesSizeY;
        const size_t TransferBufferSize =  ( BytesSquare* sizeof ( IDisplayDriver::TColor ) );

        co_await m_displayInitialized;
        co_await setAddrWindow(_x,_y,_width,_height);

        static constexpr CommandDescriptor<0x29> RamWrite{};

        co_await sendCommand(RamWrite.command.data(), RamWrite.command.size() );  //LCD_WriteCMD(GRAMWR);

        setDcPin();
        co_await sendChunk(reinterpret_cast<const std::uint8_t*>( _colorToFill ),TransferBufferSize);
        resetDcPin();
        onRectArreaFilled.emit();
    }
}

CoroUtils::VoidTask GC9A01Coro::setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
)noexcept
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

std::unique_ptr<GC9A01Coro>
createDisplayDriverCoroBasedGC9A01(
        std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
)noexcept
{
    return std::make_unique<GC9A01Coro>(
            std::move( _busPtr )
        ,   _width
        ,   _height
    );
}

};
