#pragma once 
#include <iostream>
#include <array>
#include <chrono>
#include <thread>
#include <cstdint>
#include <vector>
#include <queue>
#include <atomic>
#include <functional>
#include <coroutine>

constexpr std::uint8_t NOP = 0x00;
constexpr std::uint8_t SWRESET = 0x01;
constexpr std::uint8_t SLPIN = 0x10;
constexpr std::uint8_t SLPOUT = 0x11;
constexpr std::uint8_t NORON = 0x13;

constexpr std::uint8_t INVOFF = 0x20;
constexpr std::uint8_t INVON = 0x21;
constexpr std::uint8_t DISPOFF = 0x28;
constexpr std::uint8_t DISPON = 0x29;
constexpr std::uint8_t CASET = 0x2A;
constexpr std::uint8_t RASET = 0x2B;
constexpr std::uint8_t RAMWR = 0x2C;
constexpr std::uint8_t RAMRD = 0x2E;

constexpr std::uint8_t MADCTL = 0x36;
constexpr std::uint8_t COLMOD = 0x3A;

template< std::uint8_t ... Command>
struct CommandDescriptor {};

template<std::uint8_t Command, std::uint8_t CommandDelay, std::uint8_t ... CommandArgs>
struct CommandDescriptor< Command, CommandDelay, CommandArgs...>
{
    std::uint8_t commandDelay = CommandDelay;
    std::array<std::uint8_t, sizeof...(CommandArgs) + 1> command{ Command,CommandArgs... };
};

template<std::uint8_t Command, std::uint8_t CommandDelay>
struct CommandDescriptor<Command, CommandDelay>
{
    std::uint8_t commandDelay = CommandDelay;
    std::array<std::uint8_t, 1> command{ Command };
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


static const auto Commands = std::array<std::uint8_t, 320>
{
    /***Cmd****Argc****delay****argv*****************************/
    0xFE, 0, 0
        , 0xEF, 0, 0
        , 0xEB, 1, 0, 0x14

        , 0xFE, 0, 0
        , 0xEF, 0, 0
        , 0xEB, 1, 0, 0x14
        , 0xFE
        , 0xEF
        , 0xEB, 1, 0, 0x14

        , 0xFE
        , 0xEF

        , 0x84, 1, 0, 0x40
        , 0x85, 1, 0, 0xF1
        , 0x86, 1, 0, 0x98
        , 0x87, 1, 0, 0x28
        , 0x88, 1, 0, 0x0A
        , 0x89, 1, 0, 0x21

        , 0x8A, 1, 0, 0x00
        , 0x8B, 1, 0, 0x80
        , 0x8C, 1, 0, 0x01
        , 0x8D, 1, 0, 0x00
        , 0x8E, 1, 0, 0xDF
        , 0x8F, 1, 0, 0x52

        , 0xB6, 1, 0, 0x20

        , 0x36, 1, 0, 0x48

        , 0x3A, 1, 0, 0x05

        , 0x90, 4, 0, 0x08, 0x08, 0x08, 0x08

        , 0xBD, 1, 0, 0x06
        , 0xA6, 1, 0, 0x74
        , 0xBF, 1, 0, 0x1C
        , 0xA7, 1, 0, 0x45
        , 0xA9, 1, 0, 0xBB
        , 0xB8, 1, 0, 0x63
        , 0xE8, 1, 0, 0x34

        , 0xFF, 3, 0, 0x60, 0x01, 0x04

        , 0x74, 7, 0, 0x10, 0x75, 0x80, 0x00, 0x00, 0x4E, 0x00
        , 0xC3, 5, 0, 0x14, 0xC4, 0x14, 0xC9, 0x25

        , 0xBE, 1, 0, 0x11
        , 0xBC, 1, 0, 0x00
        , 0xE1, 2, 0, 0x10, 0x0e

        , 0xDF, 3, 0, 0x21, 0x0c, 0x02

        , 0xED, 2, 0, 0x1B, 0x0B

        , 0xAE, 5, 0, 0x77, 0xCB, 0x02, 0xCD, 0x63

        , 0x70, 9, 0, 0x07, 0x09, 0x04, 0x0e, 0x0f, 0x09, 0x07, 0x08, 0x03
        , 0xf0, 6, 0, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2a
        , 0xf1, 6, 0, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6f
        , 0xf2, 6, 0, 0x45, 0x09, 0x08, 0x08, 0x26, 0x2a
        , 0xf3, 6, 0, 0x43, 0x70, 0x72, 0x36, 0x37, 0x6f

        , 0x62, 12, 0, 0x18, 0x0d, 0x71, 0xED, 0x70, 0x70, 0x18, 0x0F, 0x71, 0xEF, 0x70, 0x70
        , 0x63, 12, 0, 0x18, 0x11, 0x71, 0xf1, 0x70, 0x70, 0x18, 0x13, 0x71, 0xf3, 0x70, 0x70
        , 0x64, 7, 0, 0x28, 0x29, 0xF1, 0x01, 0xf1, 0x00, 0x07
        , 0x66, 10, 0, 0x3c, 0x00, 0xCD, 0x67, 0x45, 0x45, 0x10, 0x00, 0x00, 0x00
        , 0x67, 10, 0, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x01, 0x54, 0x10, 0x32, 0x98
        , 0x74, 7, 0, 0x10, 0x85, 0x80, 0x00, 0x00, 0x4e, 0x00

        , 0x98, 2, 0, 0x3e, 0x07

        , 0x35, 0, 0
        , 0x21, 0, 0

        , 0x11, 0, 120
        , 0x29, 0, 0
};


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



class ST7789Coroutine
    : public DisplayDriver::BaseSpiDisplayCoroutine
{
    using BaseDisplay_t = DisplayDriver::BaseSpiDisplayCoroutine;
public:

    explicit ST7789Coroutine(
        std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
        , std::uint16_t _width
        , std::uint16_t _height
    ) : DisplayDriver::BaseSpiDisplayCoroutine(
        std::move(_busPtr)
        , _width
        , _height
    )
    {
        initDisplay();
    }

    ~ST7789Coroutine()noexcept override
    {
    }

    void initDisplay()
    {
        BaseDisplay_t::resetResetPin();
        Delay::waitFor(100);
        BaseDisplay_t::setResetPin();

        co_await launchInit(
            std::make_integer_sequence<std::size_t, std::tuple_size<decltype(CommandsArray)>::value> {}
        );

        LOG_DEBUG_ENDL("Display initialized");
        constexpr bool pushToMainQueue = true;
        m_displayInitialized.set(pushToMainQueue);
    }

    void turnOn()noexcept override
    {
    }

    void turnOff()noexcept override
    {
    }

    void fillRectangle(
        std::uint16_t _x
        , std::uint16_t _y
        , std::uint16_t _width
        , std::uint16_t _height
        , IDisplayDriver::TColor* _color
    )noexcept override
    {
        co_await fillRectImpl();
    }
private:

    template<std::size_t... Indexes>
    CoroUtils::VoidTask launchInit(std::integer_sequence<std::size_t, Indexes...>)
    {
        (co_await CoroUtils::when_all_sequence(
            sendCommand(
                std::get<Indexes>(CommandsArray).command.data()
                , std::get<Indexes>(CommandsArray).command.size()
            )
        ), ...
            );
    }

    CoroUtils::VoidTask fillRectImpl()
    {
        co_await m_displayInitialized;
        printf("CoroUtils::VoidTask fillRectImpl()\n!");
    }
private:

    void initColumnRow(
        std::uint16_t _width
        , std::uint16_t _height
    )noexcept
    {
        LOG_DEBUG_ENDL("void initColumnRow");
    }

    void setAddrWindow(
        std::uint16_t _x
        , std::uint16_t _y
        , std::uint16_t _width
        , std::uint16_t _height
    )noexcept
    {
    }
};