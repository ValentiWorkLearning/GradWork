#pragma once

#include "ih/drivers/ih_display_idisplay.hpp"
#include "gpio/gpio_pin.hpp"

#include "display_st7789v_constants.hpp"

#include "utils/SimpleSignal.hpp"

#include <memory>
#include <cstdint>

namespace Interface::Spi
{
    class SpiBus;
}

namespace DisplayDriver
{

class St7789V
        :   public IDisplayDriver
{

public:

    explicit St7789V(
            std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    );

    ~St7789V() override;

    void turnOn() override;

    void turnOff() override;

    void fillRectangle(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
        ,   IDisplayDriver::TColor* _color
    ) override;

private:

    void initDisplay();

    void sendCommand(
            std::uint8_t _command
    );

    template< typename ... Args >
    void sendCommand(
            std::uint8_t _command
        ,   Args... _commandArgs
    );

    template< typename ... Args >
    void sendChunk(
        Args... _commandArgs
    );

    void initColumnRow(
            std::uint16_t _width
        ,   std::uint16_t _height
    );

    void setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    );

private:

    void resetDcPin();

    void setDcPin();

private:
    std::uint32_t m_completedTransitionsCount;
    std::uint32_t getTransitionOffset();

private:

    std::uint8_t m_columnStart;
    std::uint8_t m_rowStart;

    const std::uint16_t m_width;
    const std::uint16_t m_height;

    Gpio::GpioPin m_dcPin;
    Gpio::GpioPin m_resetPin;
    std::unique_ptr<Interface::Spi::SpiBus> m_pBusPtr;
};

std::unique_ptr<St7789V>
createDisplayDriver(
        std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
);

}; // namespace DisplayDriver

