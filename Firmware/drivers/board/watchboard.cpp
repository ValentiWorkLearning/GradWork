#include "inc/board/watchboard.hpp"

#if defined (USE_DEVICE_SPECIFIC)
#include "pca10040.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#endif

#include "logger/logger_service.hpp"
#include "delay/delay_provider.hpp"

namespace WatchBoard
{

void initBoard()
{
#if defined (USE_DEVICE_SPECIFIC)
    /* Configure board. */
    bsp_board_init( BSP_INIT_LEDS );

    Logger::Instance().logDebugEndl( "Hello from E73 Mod Board!" );

    ret_code_t errorCode{};

    errorCode = app_timer_init();
    APP_ERROR_CHECK( errorCode );
#endif
}

void toggleStatusLed()
{
#if defined (USE_DEVICE_SPECIFIC)

    constexpr std::uint16_t DelayTime = 300;

    bsp_board_led_invert(0);
    Delay::waitFor( DelayTime );

#endif
}
};
