#include "inc/board/watchboard.hpp"

#if defined (USE_DEVICE_SPECIFIC)

#include "pca10040.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"

#endif

#include "buttons/bt_buttons_driver.hpp"
#include "buttons/bt_buttons_driver_creator.hpp"

#include "logger/logger_service.hpp"
#include "delay/delay_provider.hpp"

namespace WatchBoard
{

void
Board::initBoard()
{
#if defined (USE_DEVICE_SPECIFIC)
    /* Configure board. */
    bsp_board_init( BSP_INIT_LEDS );

    Logger::Instance().logDebugEndl( "Hello from E73 Mod Board!" );

    ret_code_t errorCode{};

    errorCode = app_timer_init();
    APP_ERROR_CHECK( errorCode );
#endif

    m_pButtonsDriver = Buttons::createButtonsDriver();
    m_pButtonsTimer = Buttons::createTimerBackend();
    m_pButtonsBackend = Buttons::createButtonsBackend();

    m_pButtonsDriver->setButtonsBackend( m_pButtonsBackend.get() );
    m_pButtonsDriver->setTimer( m_pButtonsTimer.get() );
}

void
Board::toggleStatusLed()
{
#if defined (USE_DEVICE_SPECIFIC)

    constexpr std::uint16_t DelayTime = 300;

    bsp_board_led_invert(0);
    Delay::waitFor( DelayTime );

#endif
}

Buttons::IButtonsDriver*
Board::getButtonsDriver()
{
    return m_pButtonsDriver.get();
}

Buttons::IButtonsDriver*
Board::getButtonsDriver() const
{
    return m_pButtonsDriver.get();
}

TBoardPtr createBoard()
{
    return std::make_unique<Board>();
}

};
