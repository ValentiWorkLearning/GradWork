#include "sp_battery_service_fake.hpp"

#include "CallbackConnector.hpp"
#include "MetaUtils.hpp"

namespace FakeSettings
{
    static constexpr std::uint8_t BatteryIncrement = 10;
    static constexpr std::uint8_t FakeMinBatteryLevel = 0;
    static constexpr std::uint8_t FakeMaxBatteryLevel = 100;
}

#ifdef USE_NRFSDK_SIMULATOR

#include "app_timer.h"
#include "app_error.h"

#include "sensorsim.h"

namespace
{
    /**< Battery timer. */
    APP_TIMER_DEF( m_batterySimulatorTimer );
}


namespace ServiceProviders::BatteryService
{

class BatteryServiceFake::BatterySimulatorImpl
{

public:

    BatterySimulatorImpl(
                const std::chrono::seconds _measurePeriod
            ,   const IBatteryLevelAppService* _pBatService
        )
        :   m_batteryLevel{ FakeSettings::FakeMinBatteryLevel }
        ,   m_measuringPeriod{ _measurePeriod }
        ,   m_pBatService{ _pBatService }
    {
        initSimulator();
        initTimer();
    }

public:

    std::chrono::seconds getMeasurmentPeriod() const
    {
        return m_measuringPeriod;
    }

    void startSimulation()
    {
        ret_code_t errorCode{};
        errorCode = app_timer_start(
                m_batterySimulatorTimer
            ,   convertToTimerTicks( m_measuringPeriod )
            ,   nullptr
        );
        APP_ERROR_CHECK( errorCode );
    }

private:

    void measureBatteryLevel()
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
            if( m_pBatService )
                m_pBatService->onBatteryLevelChangedSig.emit( m_batteryLevel );
        }
    }

    void timerExpiredHandler( void * _pContext )
    {
       Meta::UnuseVar( _pContext );
       measureBatteryLevel();
    }

    void initSimulator()
    {
        m_simulatorConfig.min          = FakeSettings::FakeMinBatteryLevel;
        m_simulatorConfig.max          = FakeSettings::FakeMaxBatteryLevel;
        m_simulatorConfig.incr         = FakeSettings::BatteryIncrement;
        m_simulatorConfig.start_at_max = true;

        sensorsim_init( &m_simulatorState, &m_simulatorConfig );
    }

    void initTimer()
    {
        ret_code_t errorCode{};

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
    }

    std::uint32_t convertToTimerTicks( std::chrono::seconds _interval )
    {
        std::chrono::milliseconds msValue = std::chrono::duration_cast<std::chrono::milliseconds>( _interval );
        std::uint32_t timerTicksValue = APP_TIMER_TICKS( msValue.count() );

        return timerTicksValue;
    }

private:

    std::uint8_t m_batteryLevel;

    const std::chrono::seconds m_measuringPeriod;

    const IBatteryLevelAppService* m_pBatService;

    /**< Battery Level sensor simulator configuration. */
    sensorsim_cfg_t   m_simulatorConfig;
    /**< Battery Level sensor simulator state. */
    sensorsim_state_t m_simulatorState;

};

}

#endif

#ifdef USE_DESKTOP_SIMULATOR

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <random>

namespace ServiceProviders::BatteryService
{

class BatteryServiceFake::BatterySimulatorImpl
{

public:

    BatterySimulatorImpl(
            const std::chrono::seconds _measurePeriod
        ,   const IBatteryLevelAppService* _pBatService
    )
        :
            m_batteryLevel{ FakeSettings::FakeMinBatteryLevel }
        ,   m_measuringPeriod{ _measurePeriod }
        ,   m_pBatService{ _pBatService }
        ,   m_isStopped{ true }
    {
        initSimulator();
    }

    ~BatterySimulatorImpl()
    {
        if( m_simulatorThread.joinable() )
            m_simulatorThread.join();
    }

public:

    std::chrono::seconds getMeasurmentPeriod() const
    {
        return m_measuringPeriod;
    }

    void startSimulation()
    {
        m_startMeasureNotifier.notify_one();
    }

private:

    void initSimulator()
    {
        m_isStopped.store( false );
        m_simulatorThread = std::thread(
            [this]
            {
                std::random_device radnomDevice;
                std::mt19937 generator( radnomDevice());
                std::uniform_int_distribution<> dis( 10, 100 );

                std::unique_lock locker( m_simulationStartMarker );
                m_startMeasureNotifier.wait( locker );

                while( !m_isStopped.load() )
                {
                    std::this_thread::sleep_for( m_measuringPeriod );
                    m_batteryLevel.store( dis( generator ) );

                    if ( m_pBatService )
                        m_pBatService->onBatteryLevelChangedSig.emit( m_batteryLevel );
                }
            }
       );
    }

private:

    std::thread m_simulatorThread;

    std::mutex m_simulationStartMarker;

    std::atomic<std::uint8_t> m_batteryLevel;
    std::atomic_bool m_isStopped;

    std::condition_variable m_startMeasureNotifier;

    const std::chrono::seconds m_measuringPeriod;

    const IBatteryLevelAppService* m_pBatService;
};
}
#endif

namespace ServiceProviders::BatteryService
{

BatteryServiceFake::BatteryServiceFake( std::chrono::seconds _measurementPeriod )
    :   m_pBatterySimImpl{
            std::make_unique<BatterySimulatorImpl>( _measurementPeriod , this )
        }
{
}

BatteryServiceFake::~BatteryServiceFake() = default;

std::chrono::seconds
BatteryServiceFake::getMeasurmentPeriod() const
{
    return m_pBatterySimImpl->getMeasurmentPeriod();
};

void BatteryServiceFake::startBatteryMeasure()
{
    m_pBatterySimImpl->startSimulation();
}

};
