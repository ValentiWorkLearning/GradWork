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


#include "ih/drivers/ih_display_idisplay.hpp"

#include "display/display_spi_common_coro.hpp"
#include "spi/spi_wrapper_async.hpp"
#include "logger/logger_service.hpp"


//#include <cppcoro/when_all.hpp>
//#include <cppcoro/task.hpp>

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
        CommandDescriptor<SWRESET,150>{}
    ,   CommandDescriptor<SLPOUT>{}
    ,   CommandDescriptor<COLMOD,DefaultDelay, 0x55>{}
    ,   CommandDescriptor<MADCTL,DefaultDelay, 0x08>{}
    ,   CommandDescriptor<CASET, DefaultDelay,0x00,0,0,240>{}
    ,   CommandDescriptor<RASET, DefaultDelay,0x00, 0, bitwiseResolutionConstant(), 320 & 0xFF> {}
    ,   CommandDescriptor<INVON>{}
    ,   CommandDescriptor<NORON>{}
    ,   CommandDescriptor<DISPON>{}
    ,   CommandDescriptor<MADCTL,DefaultDelay, 0xC0>{}
};


class ST7789Coroutine
    : public DisplayDriver::BaseSpiDisplayCoroutine
{
    using BaseDisplay_t = DisplayDriver::BaseSpiDisplayCoroutine;
public:

    explicit ST7789Coroutine(
            std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )   :     DisplayDriver::BaseSpiDisplayCoroutine(
            std::move(_busPtr)
        ,   _width
        ,   _height
    )
    {
        
    }

    ~ST7789Coroutine()noexcept override
    {
    }

    void initDisplay()
    {
        BaseDisplay_t::resetResetPin();
        Delay::waitFor(100);
        BaseDisplay_t::setResetPin();

        co_await std::apply(
            [this](const auto&... _commandDescriptor)->CoroUtils::VoidTask
            {
                co_await CoroUtils::when_all_sequence(
                    sendCommand(
                        _commandDescriptor.command.data()
                        , _commandDescriptor.command.size()
                    )...
                );
            }
            , CommandsArray
        );

        LOG_DEBUG_ENDL("Display initialized");
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

void initializePeripheral(ST7789Coroutine& display)
{
    display.initDisplay();
}

 int main()
 {
     /*Display display{};
     display.fillRectangle(0, 0, 220, 220, nullptr);*/

     ST7789Coroutine displayCoro{
            Interface::Spi::createSpiBusAsync<Interface::Spi::SpiInstance::M1>()
         ,  240
         ,  240
     };
     initializePeripheral(displayCoro);

     while(true)
     {
         using namespace std::chrono_literals;
         std::this_thread::sleep_for(100ms);
     }
     return 0;
 }

