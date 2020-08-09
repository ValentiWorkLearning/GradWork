#include "inc/buttons/bt_nordic_hardware_backend.hpp"

#include "utils/CallbackConnector.hpp"
#include "utils/MetaUtils.hpp"

#include "app_timer.h"
#include "app_error.h"

namespace
{
    APP_TIMER_DEF( m_buttonsDriverTimer );
}



namespace Buttons
{

NordicTimerBackend::NordicTimerBackend()
{
    ret_code_t errorCode{};

    auto timerExpiredCallback = cbc::obtain_connector(
        [ this ]( void * _pContext )
        {
            m_isTimerEllapsed = true;
        }
    );

    errorCode = app_timer_create(
            &m_buttonsDriverTimer
        ,   APP_TIMER_MODE_SINGLE_SHOT
        ,   timerExpiredCallback
    );
    APP_ERROR_CHECK( errorCode );
}

void
NordicTimerBackend::startTimer()
{

    if( !m_isTimerEllapsed )
    {
        stopTimer();
        startTimer();
    }

    ret_code_t errorCode{};
    errorCode = app_timer_start(
            m_buttonsDriverTimer
        ,   APP_TIMER_TICKS( ClicksDetectionPeriodMs )
        ,   nullptr
    );
    APP_ERROR_CHECK( errorCode );

    m_isTimerEllapsed = false;
}

void
NordicTimerBackend::stopTimer()
{
    ret_code_t errorCode{};
    errorCode = app_timer_start(
            m_buttonsDriverTimer
        ,   APP_TIMER_TICKS( ClicksDetectionPeriodMs )
        ,   nullptr
    );
    APP_ERROR_CHECK( errorCode );

    m_isTimerEllapsed = true;
}

bool
NordicTimerBackend::isTimerEllapsed() const
{
    return m_isTimerEllapsed;
}

NordicButtonsBackend::NordicButtonsBackend()
{
    initNordicButtonsBackend();
}

void
NordicButtonsBackend::initNordicButtonsBackend()
{

}

}
