#include "inc/gpio/gpio_pin.hpp"

#include <logger/logger_service.hpp>
#include <utils/MetaUtils.hpp>

#if defined(USE_DEVICE_SPECIFIC)
#include "boards.h"
#endif

namespace Gpio
{

#if defined(USE_DEVICE_SPECIFIC)
template <std::uint8_t GpioPinNumber, Direction pinDirection>
GpioPin<GpioPinNumber, pinDirection>::GpioPin() noexcept
{
    if (m_pinDirection == Direction::Output)
        nrf_gpio_cfg_output(m_pinNumber);
}

template <std::uint8_t GpioPinNumber, Direction pinDirection>
void GpioPin<GpioPinNumber, pinDirection>::set() noexcept
{
    nrf_gpio_pin_set(m_pinNumber);
}

template <std::uint8_t GpioPinNumber, Direction pinDirection>
void GpioPin<GpioPinNumber, pinDirection>::reset() noexcept
{
    nrf_gpio_pin_clear(m_pinNumber);
}

#else
template <std::uint8_t GpioPinNumber, Direction pinDirection>
GpioPin<GpioPinNumber, pinDirection>::GpioPin() noexcept = default;

template <std::uint8_t GpioPinNumber, Direction pinDirection>
void GpioPin<GpioPinNumber, pinDirection>::set() noexcept
{
    LOG_DEBUG_ENDL("Gpio Set called");
}

template <std::uint8_t GpioPinNumber, Direction pinDirection>
void GpioPin<GpioPinNumber, pinDirection>::reset() noexcept
{
    LOG_DEBUG_ENDL("Gpio Reset called");
}

#endif

template <std::uint8_t GpioPinNumber, Direction pinDirection>
GpioPin<GpioPinNumber, pinDirection>::~GpioPin() = default;

template class GpioPin<Gpio::Pins::Display_DataCommand, Direction::Output>;
}; // namespace Gpio
