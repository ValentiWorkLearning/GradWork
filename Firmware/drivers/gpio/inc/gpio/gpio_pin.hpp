#pragma once

#include <memory>

namespace Gpio::Pins
{
    extern const std::uint8_t Display_DataCommand;
    extern const std::uint8_t Display_Reset;
}//namespace Gpio::Pins

namespace Gpio
{


enum class Direction
{
        Input
    ,   Output
};

class GpioPin
{

public:

    GpioPin(
            Gpio::Direction _gpioDirection
        ,   std::uint8_t _pinNumber
    );

    ~GpioPin();

public:

    void set();

    void reset();

private:
    Direction m_pinDirection;
    std::uint8_t m_pinNumber;
};

GpioPin getGpioPin ( std::uint8_t _pinNumber, Direction _pinDirection );

} // namespace Gpio
