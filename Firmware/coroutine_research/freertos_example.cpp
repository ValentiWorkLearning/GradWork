#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>

#include "SEGGER_RTT.h"
#include "pca10040.h"
#include "boards.h"
#include "bsp.h"

#include <cstdint>

TaskHandle_t seggerLoggerTaskHandle;
TaskHandle_t ledBlinkTaskHandle;


const char FirstMessage [] = "Before suspending\n";
const char SecondMessage [] = "After restoring from suspended state\n";



static void loggerTaskFunction (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        SEGGER_RTT_WriteString(0, FirstMessage);
        taskYIELD();
        SEGGER_RTT_WriteString(0, SecondMessage);
    }
}



static void ledBlinkTaskFunction (void * pvParameter)
{
    UNUSED_PARAMETER(pvParameter);
    while (true)
    {
        bsp_board_led_invert(0);
        taskYIELD();
    }
}


int main()
{

    constexpr std::uint8_t Priority = 2;
    UNUSED_PARAMETER(
        xTaskCreate(
            loggerTaskFunction,
            "LogggerTask",
            configMINIMAL_STACK_SIZE + 200,nullptr, Priority, &seggerLoggerTaskHandle)
    );
    UNUSED_PARAMETER(
        xTaskCreate(
            ledBlinkTaskFunction,
            "LogggerTask",
            configMINIMAL_STACK_SIZE + 200,nullptr, Priority, &ledBlinkTaskHandle)
    );

    vTaskStartScheduler();
    return 0;
}