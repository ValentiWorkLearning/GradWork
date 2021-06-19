#pragma once
#include <iostream>

namespace Gpio::Pins
{
inline constexpr std::uint8_t Display_DataCommand = 0;
inline constexpr std::uint8_t Display_Reset = 0;
inline constexpr std::uint8_t LedPin = 0;

} // namespace Gpio::Pins

namespace Gpio
{

enum class Direction
{
    Input,
    Output
};

template <std::uint8_t GpioPinNumber, Direction pinDirection> class GpioPin
{

public:
    GpioPin() noexcept = default;

    ~GpioPin() = default;

public:
    void set() noexcept
    {
        std::cout << "GPIO SET CALLED\n";
    }

    void reset() noexcept
    {
        std::cout << "GPIO RESET CALLED\n";
    }

private:
    Direction m_pinDirection = pinDirection;
    std::uint8_t m_pinNumber = GpioPinNumber;
};

using DisplayDataCommandPin = GpioPin<Gpio::Pins::Display_DataCommand, Direction::Output>;
using DisplayResetPin = GpioPin<Gpio::Pins::Display_Reset, Direction::Output>;
using OnboardLedPin = GpioPin<Gpio::Pins::LedPin, Direction::Output>;

} // namespace Gpio