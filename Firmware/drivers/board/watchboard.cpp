#include "inc/board/watchboard.hpp"

#if defined(USE_DEVICE_SPECIFIC)

#include "app_error.h"
#include "app_timer.h"
#include "boards.h"
#include "bsp.h"
#include "pca10040.h"

namespace
{
APP_TIMER_DEF(m_ledDriverTimer);
}

#endif

#include "utils/CallbackConnector.hpp"
#include "utils/CoroUtils.hpp"

#include "delay/delay_provider.hpp"
#include "logger/logger_service.hpp"

#define FMT_HEADER_ONLY
#include <fmt/core.h>
#include <fmt/ranges.h>

namespace
{
static void TimerExpiredCallback(void* _pExpiredContext) noexcept
{
    std::coroutine_handle<>::from_address(_pExpiredContext).resume();
}
} // namespace

auto operator co_await(std::chrono::milliseconds _duration)
{

    class Awaitable
    {

    public:
        explicit Awaitable(std::chrono::milliseconds _duration) : m_duration{_duration}
        {
        }

        bool await_ready() const noexcept
        {
            return false;
        }
#if defined(USE_DEVICE_SPECIFIC)
        void await_suspend(std::coroutine_handle<> _coroLedHandle) noexcept
        {
            ret_code_t errorCode{};
            errorCode = app_timer_start(
                m_ledDriverTimer, APP_TIMER_TICKS(m_duration.count()), _coroLedHandle.address());
            APP_ERROR_CHECK(errorCode);
        }

        void await_resume() noexcept
        {
            app_timer_stop(m_ledDriverTimer);
        }
#else
        bool await_suspend(std::coroutine_handle<> _coroLedHandle) noexcept
        {
            return false;
        }

        void await_resume() noexcept
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

void Board::initBoard() noexcept
{
#if defined(USE_DEVICE_SPECIFIC)
    /* Configure board. */
    bsp_board_init(BSP_INIT_LEDS);

    LOG_DEBUG_ENDL("Hello from E73 Mod Board!");

    ret_code_t errorCode{};

    errorCode = app_timer_init();
    APP_ERROR_CHECK(errorCode);
#endif
    m_buttonsDriver.initializeHalDependent();
    initBoardSpiFlash();
}

void Board::initBoardTimer() noexcept
{
#if defined(USE_DEVICE_SPECIFIC)
    ret_code_t errorCode{};
    errorCode =
        app_timer_create(&m_ledDriverTimer, APP_TIMER_MODE_SINGLE_SHOT, TimerExpiredCallback);
    APP_ERROR_CHECK(errorCode);
    LOG_DEBUG("LED timer create code is:");
    LOG_DEBUG_ENDL(errorCode);
#endif
}

void Board::initBoardSpiFlash() noexcept
{
    m_pFlashDriver = std::make_unique<Hal::TFlashDriver>();
    if (m_pFlashDriver)
    {
        const std::uint32_t JedecId = co_await m_pFlashDriver->requestJEDEDCId();
        LOG_DEBUG("Jedec Id is:");
        LOG_DEBUG_ENDL(fmt::format("{:#04x}", JedecId));

        const std::span<std::uint8_t> DeviceId = co_await m_pFlashDriver->requestDeviceId();
        LOG_DEBUG_ENDL(fmt::format("{:02X}", fmt::join(DeviceId, "")));
    }
}

Board::Board() noexcept
{
    initBoard();
    initBoardTimer();
}

void Board::ledToggle() noexcept
{
#if defined(USE_DEVICE_SPECIFIC)
    using namespace std::chrono_literals;
    while (true)
    {
        co_await 300ms;
        // LOG_DEBUG_ENDL("LED TIMER EXPIRED");
        bsp_board_led_invert(0);
        co_await 100ms;
        bsp_board_led_invert(0);
        co_await 100ms;
        bsp_board_led_invert(0);
        co_await 100ms;
    }
#endif
}

std::uint32_t Board::convertToTimerTicks(std::chrono::milliseconds _interval) noexcept
{
#if defined(USE_DEVICE_SPECIFIC)
    std::uint32_t timerTicksValue = APP_TIMER_TICKS(_interval.count());
    return timerTicksValue;
#endif
    return 0;
}

Hal::ButtonsDriver* Board::getButtonsDriver() noexcept
{
    return &m_buttonsDriver;
}

TBoardPtr createBoard() noexcept
{
    return std::make_unique<Board>();
}

}; // namespace WatchBoard
