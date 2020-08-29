#include "inc/board/watchboard.hpp"

#if defined (USE_DEVICE_SPECIFIC)

#include "pca10040.h"
#include "boards.h"
#include "bsp.h"
#include "app_timer.h"
#include "app_error.h"

namespace
{
    APP_TIMER_DEF( m_ledDriverTimer );
}

#endif

#include "utils/CallbackConnector.hpp"

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

    LOG_DEBUG_ENDL( "Hello from E73 Mod Board!" );

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
Board::initBoardTimer()
{
#if defined (USE_DEVICE_SPECIFIC)
    ret_code_t errorCode{};

    auto timerExpiredCallback = cbc::obtain_connector(
        [ this ]( void * _pContext )
        {
            LOG_DEBUG_ENDL("LED TIMER EXPIRED");
            bsp_board_led_invert(0);
        }
    );

    errorCode = app_timer_create(
            &m_ledDriverTimer
        ,   APP_TIMER_MODE_REPEATED
        ,   timerExpiredCallback
    );
    APP_ERROR_CHECK( errorCode );
#endif
}

Board::Board()
{
    initBoard();
    initBoardTimer();
}

void
Board::enableLedToggle()
{
#if defined (USE_DEVICE_SPECIFIC)
    ret_code_t errorCode{};
    errorCode = app_timer_start(
            m_ledDriverTimer
        ,   convertToTimerTicks(LedToggleTimeout)
        ,   nullptr
    );
    APP_ERROR_CHECK( errorCode );
#endif
}

std::uint32_t
Board::convertToTimerTicks( std::chrono::milliseconds _interval )
{
#if defined (USE_DEVICE_SPECIFIC)
    std::uint32_t timerTicksValue = APP_TIMER_TICKS( _interval.count() );
    return timerTicksValue;
#endif
    return 0;
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
