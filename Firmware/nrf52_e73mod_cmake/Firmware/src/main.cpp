#include <cstdint>
#include <string>


#include "nrf_delay.h"
#include "nrf.h"
#include "boards.h"

#include "app_uart.h"
#include "app_error.h"
#include "bsp.h"

#include "drivers/display/display_st7789v_constants.hpp"
#include "drivers/display/display_st7789v.hpp"

#include "drivers/spi/spi_wrapper.hpp"

#include "drivers/ble/ble_custom_service.hpp"
#include "drivers/ble/ble_softdevice.hpp"

#include "logger/logger_service.hpp"


int main(void)
{
    /* Configure board. */
    bsp_board_init( BSP_INIT_LEDS );

    Logger::Instance().logDebug( "Hello world!" );

    auto spiInstance = Interface::Spi::createSpiBus<Interface::Spi::SpiInstance::M0>();

    auto display = DisplayDriver::createDisplayDriver(
            spiInstance.get()
        ,   DisplayDriver::St7789v::Disp208_240::Width
        ,   DisplayDriver::St7789v::Disp208_240::Height
    );

    auto bleStackKeeper = Ble::Stack::createBleStackKeeper();

    nrf_delay_ms(230);

    display->fillColor( DisplayDriver::Colors::BLACK );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::WHITE );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::RED );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::GREEN );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::BLUE );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::CYAN );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::MAGENTA );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::YELLOW );
    nrf_delay_ms(120);
    display->fillColor( DisplayDriver::Colors::ORANGE );
    nrf_delay_ms(120);
    display->fillRectangle( 40,40,20,20,DisplayDriver::Colors::BLACK );
    nrf_delay_ms(120);
    /* Toggle LEDs. */
    auto ledToggler = 
    []( size_t _delayTime )
    {
        bsp_board_led_invert(0);
        nrf_delay_ms( _delayTime );
    };

    while (true)
    {
        ledToggler( 300 );
    }
}
