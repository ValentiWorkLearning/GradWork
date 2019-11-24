#include "sp_battery_service_fake.hpp"

#include "CallbackConnector.hpp"

#include "app_timer.h"
#include "app_error.h"

namespace
{
    /**< Battery timer. */
    APP_TIMER_DEF( m_batterySimulatorTimer );
}

namespace ServiceProviders::BatteryService
{

BatteryServiceFake::BatteryServiceFake( std::chrono::seconds _measurementPeriod )
    :   m_batteryLevel{}
    ,   m_measuringPeriod{ _measurementPeriod }
{
    initSimulator();
    initTimer();
}

void
BatteryServiceFake::setMeasurmentPeriod(
    const std::chrono::seconds _measurementPeriod
    )
{
    m_measuringPeriod = _measurementPeriod;
}

std::chrono::seconds
BatteryServiceFake::getMeasurmentPeriod() const
{
    return m_measuringPeriod;
};

void BatteryServiceFake::measureBatteryLevel()
{
    std::uint8_t measuredBatteryLevel =
        static_cast<std::uint8_t>( sensorsim_measure(
                    &m_simulatorState
                ,   &m_simulatorConfig
            )
        );

    if(  m_batteryLevel != measuredBatteryLevel )
    {
        m_batteryLevel = measuredBatteryLevel;
        onBatteryLevelChangedSig.emit( m_batteryLevel );
    }
}

void
BatteryServiceFake::timerExpiredHandler( void * _pContext )
{
    measureBatteryLevel();
}

void
BatteryServiceFake::initSimulator()
{
    m_simulatorConfig.min          = FakeMinBatteryLevel;
    m_simulatorConfig.max          = FakeMaxBatteryLevel;
    m_simulatorConfig.incr         = BatteryIncrement;
    m_simulatorConfig.start_at_max = true;

    sensorsim_init( &m_simulatorState, &m_simulatorConfig );
}

void
BatteryServiceFake::initTimer()
{
    ret_code_t errorCode{};

    errorCode = app_timer_init();
    APP_ERROR_CHECK( errorCode );

    auto timerExpiredCallback = cbc::obtain_connector(
        [ this ]( void * _pContext )
        {
            return timerExpiredHandler( _pContext );
        }
    );

    errorCode = app_timer_create(
            &m_batterySimulatorTimer
        ,   APP_TIMER_MODE_REPEATED
        ,   timerExpiredCallback
    );
    APP_ERROR_CHECK( errorCode );

    errorCode = app_timer_start(
            m_batterySimulatorTimer
        ,   std::chrono::duration_cast<std::chrono::milliseconds>( m_measuringPeriod ).count()
        ,   nullptr
    );
    APP_ERROR_CHECK( errorCode );
}

};
