#pragma once

#include <memory>

#if defined(USE_DEVICE_SPECIFIC)
#include "pca10040.h"
#endif

namespace Gpio::Pins
{
#if defined(USE_DEVICE_SPECIFIC)
inline constexpr std::uint8_t Display_DataCommand = DISP_DC_PIN;
inline constexpr std::uint8_t Display_Reset = DISP_RST;
inline constexpr std::uint8_t LedPin = 13;
#else
inline constexpr std::uint8_t Display_DataCommand = 0;
inline constexpr std::uint8_t Display_Reset = 0;
inline constexpr std::uint8_t LedPin = 0;
#endif

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
    GpioPin() noexcept;

    ~GpioPin();

public:
    void set() noexcept;

    void reset() noexcept;

private:
    Direction m_pinDirection = pinDirection;
    std::uint8_t m_pinNumber = GpioPinNumber;
};

using DisplayDataCommandPin = GpioPin<Gpio::Pins::Display_DataCommand, Direction::Output>;
using DisplayResetPin = GpioPin<Gpio::Pins::Display_Reset, Direction::Output>;
using OnboardLedPin = GpioPin<Gpio::Pins::LedPin, Direction::Output>;

} // namespace Gpio
