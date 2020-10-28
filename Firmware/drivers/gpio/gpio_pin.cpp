#include "inc/gpio/gpio_pin.hpp"

#if defined (USE_DEVICE_SPECIFIC)
    #include "pca10040.h"

// https://cookierobotics.com/032/ useful for such constans declaration

const std::uint8_t Gpio::Pins::Display_DataCommand = DISP_DC_PIN;
const std::uint8_t Gpio::Pins::Display_Reset = DISP_RST;

#else
const std::uint8_t Gpio::Pins::Display_DataCommand = 0;
const std::uint8_t Gpio::Pins::Display_Reset = 0;
#endif
#include "utils/MetaUtils.hpp"
#include "logger/logger_service.hpp"

namespace Gpio
{

#if defined (USE_DEVICE_SPECIFIC)
GpioPin::GpioPin(
            Gpio::Direction _direction
        ,   std::uint8_t _pinNumber
    )
    :   m_pinDirection{ _direction }
    ,   m_pinNumber{ _pinNumber }
{
     if( _direction ==  Direction::Output )
        nrf_gpio_cfg_output( m_pinNumber );
}

void
GpioPin::set()
{
    nrf_gpio_pin_set( m_pinNumber );
}

void
GpioPin::reset()
{
    nrf_gpio_pin_clear( m_pinNumber );
}

#else
GpioPin::GpioPin(
       Gpio::Direction _direction
     ,  std::uint8_t _pinNumber
    )
    :   m_pinDirection{ _direction }
    ,   m_pinNumber{ _pinNumber }
{
    Meta::UnuseVar( _pinNumber );
    Meta::UnuseVar( _direction );
}

void
GpioPin::set()
{
    LOG_DEBUG_ENDL( "Gpio Set called" );
}

void
GpioPin::reset()
{
    LOG_DEBUG_ENDL( "Gpio Reset called" );
}

#endif

GpioPin::~GpioPin() = default;

GpioPin getGpioPin ( std::uint8_t _pinNumber, Direction _pinDirection )
{
    return GpioPin( _pinDirection, _pinNumber );
}

};
