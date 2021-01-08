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

#include "windbondflash/winbond_driver_creator.hpp"

#endif

#include "utils/CallbackConnector.hpp"
#include "utils/CoroUtils.hpp"

#include "buttons/bt_buttons_driver.hpp"
#include "buttons/bt_buttons_driver_creator.hpp"

#include "logger/logger_service.hpp"
#include "delay/delay_provider.hpp"

namespace
{
    static void TimerExpiredCallback( void* _pExpiredContext )
    {
        std::coroutine_handle<>::from_address(_pExpiredContext).resume();
    }
}

auto operator co_await( std::chrono::milliseconds _duration)
{

    class Awaitable
    {

        public:

        explicit Awaitable(std::chrono::milliseconds _duration)
            :   m_duration{_duration}
        {
        }

        bool await_ready()const
        {
            return false;
        }
#if defined (USE_DEVICE_SPECIFIC)
        void await_suspend(std::coroutine_handle<> _coroLedHandle)
        {
            ret_code_t errorCode{};
            errorCode = app_timer_start(
                    m_ledDriverTimer
                ,   APP_TIMER_TICKS( m_duration.count() )
                ,   _coroLedHandle.address()
            );
            APP_ERROR_CHECK( errorCode );
        }

        void await_resume()
        {
            app_timer_stop(m_ledDriverTimer);
        }
#else
        bool await_suspend(std::coroutine_handle<> _coroLedHandle)
        {
            return false;
        }

        void await_resume()
        {
        }
#endif
        private:

        std::chrono::milliseconds m_duration;

    };
    return Awaitable{_duration};
}

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

    initBoardSpiFlash();
}

void
Board::initBoardTimer()
{
#if defined (USE_DEVICE_SPECIFIC)
    ret_code_t errorCode{};
    errorCode = app_timer_create(
            &m_ledDriverTimer
        ,   APP_TIMER_MODE_SINGLE_SHOT
        ,   TimerExpiredCallback
    );
    APP_ERROR_CHECK(errorCode);
    LOG_DEBUG("LED timer create code is:");
    LOG_DEBUG_ENDL(errorCode);
#endif
}

void
Board::initBoardSpiFlash()
{
#if defined (USE_DEVICE_SPECIFIC)

    m_pFlashDriver = ExternalFlash::createExternalFlashDriver();
    if( m_pFlashDriver )
    {
        m_pFlashDriver->onRequestDeviceIdCompleted.connect(
            [this]
            {
                auto deviceId = m_pFlashDriver->getDeviceUniqueId();
                LOG_DEBUG_ENDL( deviceId );
            }
        );

        m_pFlashDriver->onRequestJedecIdCompleted.connect(
            [this]( std::uint32_t _jedecId )
            {
                LOG_DEBUG("Jedec Id is:");
                LOG_DEBUG_ENDL( _jedecId );
            }
        );

        m_pFlashDriver->requestDeviceId();
        m_pFlashDriver->requestJEDEDCId();
    }
#endif
}

Board::Board()
{
    initBoard();
    initBoardTimer();
}

void
Board::ledToggle()
{
#if defined (USE_DEVICE_SPECIFIC)
    using namespace std::chrono_literals;
    while(true)
    {
        co_await 300ms;

        //LOG_DEBUG_ENDL("LED TIMER EXPIRED");
        bsp_board_led_invert(0);
    }
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
