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

namespace UartConstants
{
    constexpr std::uint16_t TxSize = 256;        /**< max number of test bytes to be used for tx and rx. */
    constexpr std::uint16_t RxSize = TxSize;     /**< UART TX buffer size. */
    constexpr std::uint8_t TestDataBytes = 15;   /**< UART RX buffer size. */

    static const std::string HelloWorld = "Hello from E73 nordic board!\r\n";
};

namespace SwoPrint
{
    static const std::string SwoTest = "SwoTest complited! \r\n";
}


void uart_error_handle(app_uart_evt_t * p_event)
{
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    }
    else if (p_event->evt_type == APP_UART_FIFO_ERROR)
    {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

void initUartModule()
{
    std::uint32_t err_code{};

    const app_uart_comm_params_t comm_params =
    {
            RX_PIN_NUMBER
        ,   TX_PIN_NUMBER
        ,   RTS_PIN_NUMBER
        ,   CTS_PIN_NUMBER
        ,   APP_UART_FLOW_CONTROL_DISABLED
        ,   false
        ,   UART_BAUDRATE_BAUDRATE_Baud115200
    };

    APP_UART_FIFO_INIT(
            &comm_params
        ,   UartConstants::RxSize
        ,   UartConstants::TxSize
        ,   uart_error_handle
        ,   APP_IRQ_PRIORITY_LOWEST
        ,   err_code
    );

    APP_ERROR_CHECK(err_code);
}


void initSwoPrint()
{
    NRF_CLOCK->TRACECONFIG =
        ( NRF_CLOCK->TRACECONFIG & ~CLOCK_TRACECONFIG_TRACEPORTSPEED_Msk )
    |   ( CLOCK_TRACECONFIG_TRACEPORTSPEED_4MHz << CLOCK_TRACECONFIG_TRACEPORTSPEED_Pos );

    ITM->TCR |= 1;  
    ITM->TER |= 1;  
}

int main(void)
{
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    initUartModule();

    initSwoPrint();

    auto ServiceUuidBe = Ble::CustomService::UUID_BE;
    // auto ServiceUuid = Ble::CustomService::UUID_LE;
    auto Something = Ble::CustomService::reverseByteOrder(Ble::CustomService::UUID_BE);

    auto spiInstance = Interface::Spi::createSpiBus<Interface::Spi::SpiInstance::M0>();

    auto display = DisplayDriver::createDisplayDriver(
            spiInstance.get()
        ,   DisplayDriver::St7789v::Disp208_240::Width
        ,   DisplayDriver::St7789v::Disp208_240::Height
    );
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

    auto uartWriter = 
    []
    {
        for( const auto ch : UartConstants::HelloWorld )
           app_uart_put( static_cast<std::uint8_t>( ch ) );
    };

    auto swoPrinter =
    []
    {
        for( const auto ch : SwoPrint::SwoTest )
            ITM_SendChar( ch );
    };

    while (true)
    {
        ledToggler( 300 );
        uartWriter();
        swoPrinter();
    }
}
