#include "gpio_pin.hpp"
#include "pca10040.h"

namespace Gpio
{

class GpioPin::GpioPlatformImpl
{

public:

    GpioPlatformImpl( std::uint16_t _pinNumber, Gpio::Direction _pinDirection )
        :   m_pinNumber{ _pinNumber }
    {
        if( _pinDirection ==  Direction::Output )
            nrf_gpio_cfg_output( m_pinNumber );
    }

public:

    void set()
    {
        nrf_gpio_pin_set( m_pinNumber );
    }

    void reset()
    {
        nrf_gpio_pin_clear( m_pinNumber );
    }

private:
    std::uint16_t m_pinNumber;
};

GpioPin::GpioPin( std::uint16_t _pinNumber, Gpio::Direction _pinDirection )
  :   m_pGpioBackendImpl{ _pinNumber, _pinDirection }
{
}

GpioPin::~GpioPin() = default;

void
GpioPin::set()
{
    m_pGpioBackendImpl->set();
}

void
GpioPin::reset()
{
    m_pGpioBackendImpl->reset();
}

GpioPin getGpioPin( std::uint16_t _pinNumber, Direction _pinDirection )
{
    return GpioPin( _pinNumber, _pinDirection );
}

}