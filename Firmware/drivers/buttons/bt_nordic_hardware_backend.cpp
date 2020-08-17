#include "inc/buttons/bt_nordic_hardware_backend.hpp"

#include "utils/CallbackConnector.hpp"
#include "utils/MetaUtils.hpp"

#include "app_timer.h"
#include "app_error.h"
#include "app_button.h"

#include "pca10040.h"

#include "logger/logger_service.hpp"

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
            Logger::Instance().logDebugEndl("m_isTimerEllapsed = true;");
        }
    );

    errorCode = app_timer_create(
            &m_buttonsDriverTimer
        ,   APP_TIMER_MODE_SINGLE_SHOT
        ,   timerExpiredCallback
    );
    APP_ERROR_CHECK( errorCode );
}


std::uint32_t
NordicTimerBackend::convertToTimerTicks( std::chrono::seconds _interval )
{
    std::chrono::milliseconds msValue = std::chrono::duration_cast<std::chrono::milliseconds>( _interval );
    std::uint32_t timerTicksValue = APP_TIMER_TICKS( msValue.count() );
    return timerTicksValue;
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
        ,   convertToTimerTicks(m_buttonLongPressDetectionDelay)
        ,   nullptr
    );
    APP_ERROR_CHECK( errorCode );

    m_isTimerEllapsed = false;
}

void
NordicTimerBackend::stopTimer()
{
    ret_code_t errorCode{};
    errorCode = app_timer_stop( m_buttonsDriverTimer );
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

    ret_code_t errorCode{};

    constexpr std::uint8_t ButtonsCount = BUTTONS_NUMBER;
    using TButtonsDescriptor = std::array<app_button_cfg_t,ButtonsCount>;

    auto buttonEventCallback = cbc::obtain_connector(
        [ this ](uint8_t _pinNumber, uint8_t _buttonAction)
        {
            handleHardwareButtonEvent( _pinNumber,_buttonAction );
        }
    );

    static TButtonsDescriptor BoardButtons = 
    {
            app_button_cfg_t{ BUTTON_1, APP_BUTTON_ACTIVE_LOW, BUTTON_PULL, buttonEventCallback }
        ,   app_button_cfg_t{ BUTTON_2, APP_BUTTON_ACTIVE_LOW, BUTTON_PULL, buttonEventCallback }
        ,   app_button_cfg_t{ BUTTON_3, APP_BUTTON_ACTIVE_LOW, BUTTON_PULL, buttonEventCallback }
        ,   app_button_cfg_t{ BUTTON_4, APP_BUTTON_ACTIVE_LOW, BUTTON_PULL, buttonEventCallback }
    };

    constexpr auto ButtonDetectionDelay = APP_TIMER_TICKS(50);
    errorCode = app_button_init(
            BoardButtons.data()
        ,   BoardButtons.size()
        ,   ButtonDetectionDelay
    );
    APP_ERROR_CHECK( errorCode );

    errorCode = app_button_enable();
    APP_ERROR_CHECK( errorCode );
}

void
NordicButtonsBackend::handleHardwareButtonEvent( std::uint8_t _pinNumber, std::uint8_t _buttonEvent )
{
    auto toLocalEvent = []( std::uint8_t _buttonEvent )
    {
        if( _buttonEvent == APP_BUTTON_PUSH )
        {
            Logger::Instance().logDebugEndl("ButtonBackendEvent::kPressed");
            return ButtonBackendEvent::kPressed;
        }
        else if( _buttonEvent == APP_BUTTON_RELEASE )
        {
            Logger::Instance().logDebugEndl("ButtonBackendEvent::kReleased");
            return ButtonBackendEvent::kReleased;
        }
        else{
            assert(false);
            return ButtonBackendEvent::kPressed;
        }
    };

    switch (_pinNumber)
    {
    case BUTTON_1:
        Logger::Instance().logDebugEndl("BUTTON_1");
        onButtonEvent.emit( Buttons::ButtonId::kLeftButtonTop, toLocalEvent( _buttonEvent ) );
        break;
    case BUTTON_2:
        Logger::Instance().logDebugEndl("BUTTON_2");
        onButtonEvent.emit( Buttons::ButtonId::kLeftButtonMedium, toLocalEvent( _buttonEvent ));
        break;
    case BUTTON_3:
        Logger::Instance().logDebugEndl("BUTTON_3");
        onButtonEvent.emit( Buttons::ButtonId::kLeftButtonBottom, toLocalEvent( _buttonEvent ));
        break;
    case BUTTON_4:
        Logger::Instance().logDebugEndl("BUTTON_4");
        onButtonEvent.emit( Buttons::ButtonId::kRightButtonTop, toLocalEvent( _buttonEvent ));
        break;
    default:
        break;
    }
}
}
