#include "sp_datetime_service_fake.hpp"

#include "CallbackConnector.hpp"


#ifdef USE_NRFSDK_SIMULATOR

#include "app_timer.h"
#include "app_error.h"

#include "sensorsim.h"

namespace
{
    /**< Battery timer. */
    APP_TIMER_DEF(m_clockSimulatorTimer);
}

namespace ServiceProviders::DateTimeService
{

class DateTimeServiceFake::DatetimeSimulatorImpl
{

public:

    DatetimeSimulatorImpl(
            const IDateTimeService* _pAppService
    )
        :   m_pDateTimeService{ _pAppService }
    {
        initSimulator();
    }

    ~DatetimeSimulatorImpl()
    {
    }

public:

    void launchService()
    {
        ret_code_t errorCode{};
        errorCode = app_timer_start(
                m_clockSimulatorTimer
            ,   convertToTimerTicks( std::chrono::seconds(1) )
            ,   nullptr
        );
        APP_ERROR_CHECK( errorCode );
    }

    void calibrateSource()
    {
    }

    void syncronizeWithBleDts()
    {
    }

private:

    void initSimulator()
    {
        ret_code_t errorCode{};

        auto timerExpiredCallback = cbc::obtain_connector(
            [ this ]( void * _pContext )
            {
                return timerExpiredHandler( _pContext );
            }
        );

        errorCode = app_timer_create(
                &m_clockSimulatorTimer
            ,   APP_TIMER_MODE_REPEATED
            ,   timerExpiredCallback
        );
        APP_ERROR_CHECK( errorCode );
    }

    void timerExpiredHandler( void * _pContext )
    {
       m_timeWrapper.addSecond();
       m_pDateTimeService->onDateTimeChanged.emit( m_timeWrapper );
    }

private:

    std::uint32_t convertToTimerTicks( std::chrono::seconds _interval )
    {
        std::chrono::milliseconds msValue = std::chrono::duration_cast<std::chrono::milliseconds>( _interval );
        std::uint32_t timerTicksValue = APP_TIMER_TICKS( msValue.count() );

        return timerTicksValue;
    }

private:

    TimeWrapper m_timeWrapper;

    const IDateTimeService* m_pDateTimeService;
};
}


#endif

#ifdef USE_DESKTOP_SIMULATOR

#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>

namespace ServiceProviders::DateTimeService
{

class DateTimeServiceFake::DatetimeSimulatorImpl
{

public:

    DatetimeSimulatorImpl(
            const IDateTimeService* _pAppService
    )
        :   m_pDateTimeService{ _pAppService }
        ,   m_isStopped{ true }
    {
        initSimulator();
    }

    ~DatetimeSimulatorImpl()
    {
        if( m_simulatorThread.joinable() )
            m_simulatorThread.join();
    }

public:

    void launchService()
    {
        m_timeGenerator.notify_one();
    }

    void calibrateSource()
    {
    }

    void syncronizeWithBleDts()
    {
    }

private:

    void initSimulator()
    {
        m_isStopped.store( false );
        m_simulatorThread = std::thread(
            [this]
            {
                using namespace std::chrono_literals;

                std::unique_lock locker( m_simulationStartMarker );
                m_timeGenerator.wait( locker );

                while( !m_isStopped.load() )
                {
                    std::this_thread::sleep_for( 1s );
                    TimeWrapper tempWrapper = m_timeWrapper.load( std::memory_order_acquire );
                    tempWrapper.addSecond();
                    m_timeWrapper.store( tempWrapper, std::memory_order_release );
                    m_pDateTimeService->onDateTimeChanged.emit( tempWrapper );
                }
            }
       );
    }

private:

    std::atomic<TimeWrapper> m_timeWrapper;

    std::thread m_simulatorThread;

    std::mutex m_simulationStartMarker;

    std::atomic_bool m_isStopped;

    std::condition_variable m_timeGenerator;

    const IDateTimeService* m_pDateTimeService;
};
}

#endif


namespace ServiceProviders::DateTimeService
{

DateTimeServiceFake::DateTimeServiceFake( )
    :   m_pDatetimeSimImpl{ this }
{
}

DateTimeServiceFake::~DateTimeServiceFake() = default;

void
DateTimeServiceFake::launchService()
{
    return m_pDatetimeSimImpl->launchService();
};

void
DateTimeServiceFake::calibrateSource()
{
    m_pDatetimeSimImpl->calibrateSource();
}

void
DateTimeServiceFake::syncronizeWithBleDts()
{
    m_pDatetimeSimImpl->syncronizeWithBleDts();
}

};
