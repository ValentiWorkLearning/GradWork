#include "sp_datetime_service_fake.hpp"

#include "utils/CallbackConnector.hpp"

#ifdef USE_NRFSDK_SIMULATOR

#include "app_error.h"
#include "app_timer.h"

#include "sensorsim.h"

namespace
{
/**< Battery timer. */
APP_TIMER_DEF(m_clockSimulatorTimer);
} // namespace

namespace ServiceProviders::DateTimeService
{

class DateTimeServiceFake::DatetimeSimulatorImpl
{

public:
    explicit DatetimeSimulatorImpl(const IDateTimeService* _pAppService)
        : m_pDateTimeService{_pAppService}
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
            m_clockSimulatorTimer, convertToTimerTicks(std::chrono::seconds(1)), nullptr);
        APP_ERROR_CHECK(errorCode);
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
            [this](void* _pContext) { return timerExpiredHandler(_pContext); });

        errorCode =
            app_timer_create(&m_clockSimulatorTimer, APP_TIMER_MODE_REPEATED, timerExpiredCallback);
        APP_ERROR_CHECK(errorCode);
    }

    void timerExpiredHandler(void* _pContext)
    {
        m_timeWrapper.addSecond();
        m_pDateTimeService->onDateTimeChanged.emit(m_timeWrapper);
    }

private:
    std::uint32_t convertToTimerTicks(std::chrono::seconds _interval)
    {
        std::chrono::milliseconds msValue =
            std::chrono::duration_cast<std::chrono::milliseconds>(_interval);
        std::uint32_t timerTicksValue = APP_TIMER_TICKS(msValue.count());

        return timerTicksValue;
    }

private:
    TimeWrapper m_timeWrapper;

    const IDateTimeService* m_pDateTimeService;
};
} // namespace ServiceProviders::DateTimeService

#endif

#ifdef USE_DESKTOP_SIMULATOR

#ifdef WIN32
#include <atomic>
#include <condition_variable>
#include <coroutine>
#include <mutex>
#include <thread>
#include <windows.h>
#include <winnt.h>

using namespace std::literals;

// https://luncliff.github.io/posts/Exploring-MSVC-Coroutine.html
// operator overload.
// co_await can't use primitive type parameter.
auto operator co_await(std::chrono::system_clock::duration _duration)
{
    // Awaitable must implements 3 function.
    //  - bool await_ready();
    //  - auto await_suspend();
    //  - T    await_resume();

    class Awaiter
    {

    public:
        static void CALLBACK TimerCallback(PTP_CALLBACK_INSTANCE, void* _context, PTP_TIMER)
        {
            std::coroutine_handle<>::from_address(_context).resume();
        }

        explicit Awaiter(std::chrono::system_clock::duration _duration)
            : m_duration{_duration}, m_pTimer{}
        {
        }

        bool await_ready() const
        {
            return m_duration.count() <= 0;
        }

        bool await_suspend(std::coroutine_handle<> _resumeCallback)
        {
            std::int64_t relativeCount = -m_duration.count();
            m_pTimer.reset(
                CreateThreadpoolTimer(TimerCallback, _resumeCallback.address(), nullptr));
            SetThreadpoolTimer(m_pTimer.get(), reinterpret_cast<PFILETIME>(&relativeCount), 0, 0);

            return m_pTimer != nullptr;
        }

        void await_resume()
        {
        }

    private:
        Meta::PointerWrapper<TP_TIMER, CloseThreadpoolTimer> m_pTimer;
        std::chrono::system_clock::duration m_duration;
    };

    return Awaiter{_duration};
}

template <typename... Args> struct std::coroutine_traits<void, Args...>
{
    struct promise_type
    {
        void get_return_object()
        {
        }
        std::suspend_never initial_suspend()
        {
            return {};
        }
        std::suspend_never final_suspend() noexcept
        {
            return {};
        }
        void return_void()
        {
        }
        void unhandled_exception()
        {
            std::terminate();
        }
    };
};



namespace ServiceProviders::DateTimeService
{

class DateTimeServiceFake::DatetimeSimulatorImpl
{

public:
public:
    explicit DatetimeSimulatorImpl(const IDateTimeService* _pAppService)
        : m_pDateTimeService{_pAppService}, m_isStopped{true}
    {
        m_timeWrapper.store(TimeWrapper("1971/01/9 13:24:43", '/', ':'));
        initSimulator();
    }

    ~DatetimeSimulatorImpl() = default;

public:
    void launchService() noexcept
    {
    }

    void calibrateSource() noexcept
    {
    }

    void syncronizeWithBleDts() noexcept
    {
    }

private:
    void initSimulator() noexcept
    {
        m_isStopped.store(false);
        while (!m_isStopped)
        {
            co_await 1s;
            TimeWrapper tempWrapper = m_timeWrapper.load(std::memory_order_acquire);
            tempWrapper.addSecond();
            m_timeWrapper.store(tempWrapper, std::memory_order_release);
            m_pDateTimeService->onDateTimeChanged.emit(tempWrapper);
        }
    }

private:
    std::atomic<TimeWrapper> m_timeWrapper;
    std::atomic_bool m_isStopped;
    const IDateTimeService* m_pDateTimeService;
};

} // namespace ServiceProviders::DateTimeService
#else

namespace ServiceProviders::DateTimeService
{

class DateTimeServiceFake::DatetimeSimulatorImpl
{

public:
public:
    explicit DatetimeSimulatorImpl(const IDateTimeService* _pAppService)
        : m_pDateTimeService{_pAppService}
    {
        initSimulator();
    }

    ~DatetimeSimulatorImpl() = default;

public:
    void launchService() noexcept
    {
    }

    void calibrateSource() noexcept
    {
    }

    void syncronizeWithBleDts() noexcept
    {
    }

private:
    void initSimulator() noexcept
    {
         m_pDateTimeService->onDateTimeChanged.emit(TimeWrapper("1971/01/9 13:24:43", '/', ':'));
    }

private:
    const IDateTimeService* m_pDateTimeService;
};
}
#endif//WIN32

#endif //FIRMWARE_SIMULATOR

namespace ServiceProviders::DateTimeService
{

DateTimeServiceFake::DateTimeServiceFake() noexcept
    : m_pDatetimeSimImpl{std::make_unique<DatetimeSimulatorImpl>(this)}
{
}

DateTimeServiceFake::~DateTimeServiceFake() = default;

void DateTimeServiceFake::launchService() noexcept
{
    return m_pDatetimeSimImpl->launchService();
};

void DateTimeServiceFake::calibrateSource() noexcept
{
    m_pDatetimeSimImpl->calibrateSource();
}

void DateTimeServiceFake::syncronizeWithBleDts() noexcept
{
    m_pDatetimeSimImpl->syncronizeWithBleDts();
}

}; // namespace ServiceProviders::DateTimeService
