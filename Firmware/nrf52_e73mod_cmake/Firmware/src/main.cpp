/**
 * Copyright (c) 2014 - 2019, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

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

/**
 * @brief Function for application main entry.
 */
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

/**
 *@}
 **/
