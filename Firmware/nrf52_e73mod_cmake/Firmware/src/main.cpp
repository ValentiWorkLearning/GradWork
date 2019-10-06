#include <cstdint>
#include <string>


#include "nrf_delay.h"
#include "nrf.h"
#include "boards.h"

#include "app_uart.h"
#include "app_error.h"
#include "bsp.h"

namespace UartConstants
{
    static constexpr std::uint16_t TxSize = 256;        /**< max number of test bytes to be used for tx and rx. */
    static constexpr std::uint16_t RxSize = TxSize;     /**< UART TX buffer size. */
    static constexpr std::uint8_t TestDataBytes = 15;   /**< UART RX buffer size. */

    static const std::string HelloWorld = "Hello from E73 nordic board!\r\n";
};


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

int main(void)
{
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    initUartModule();

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

    while (true)
    {
        ledToggler( 300 );
        uartWriter();
    }
}
