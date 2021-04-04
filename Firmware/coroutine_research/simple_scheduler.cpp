#include <utils/SimpleResumable.hpp>
#include <utils/SimpleTaskScheduler.hpp>
#include <utils/MetaUtils.hpp>

#include <coroutine>

#if defined USE_DEVICE_SPECIFIC_OPTIONS
#include "SEGGER_RTT.h"
#include "pca10040.h"
#include "boards.h"
#include "bsp.h"
#else
#include <cstdio>
#endif

void logString(const char* const stringToLog)noexcept
{
    #if defined USE_DEVICE_SPECIFIC_OPTIONS
        SEGGER_RTT_WriteString(0, stringToLog);
    #else
       printf(stringToLog);
    #endif
}

void ledToggle()noexcept
{
#if defined USE_DEVICE_SPECIFIC_OPTIONS
    bsp_board_led_invert(0);
#else
    printf("ToggleLed\n");
#endif
}

constexpr inline auto FirstMessage = "Before suspending\n";
constexpr inline auto SecondMessage = "After restoring from suspended state\n";


Resumable loggerFunction() noexcept
{
    while(true){
        logString(FirstMessage);
        co_await std::suspend_always{};
        logString(SecondMessage);
        co_await std::suspend_always{};
    }
}


Resumable ledBlinker() noexcept
{
    while(true){
        co_await std::suspend_always{};
        ledToggle();
    }
}

int main()
{
    #if defined USE_DEVICE_SPECIFIC_OPTIONS
        bsp_board_init( BSP_INIT_LEDS );
    #endif

    auto loggerTask = loggerFunction();
    auto ledBlinkTask = ledBlinker();

    auto Scheduler = TaskScheduler::SimpleCooperativeNonPriorityScheduler{};
    Scheduler.pushTask(loggerTask.getSuspendedCoroHandle());
    Scheduler.pushTask(ledBlinkTask.getSuspendedCoroHandle());

    Scheduler.runTasks();

    return 0;
}