#include "inc/logger/logger_service.hpp"

#include "utils/CallbackConnector.hpp"

#include <atomic>
#include <type_traits>

#if defined(LoggerUart)
#include "app_error.h"
#include "app_uart.h"
#include "boards.h"
#include "bsp.h"
#include "nrf.h"
#elif defined(LoggerSwo)
#include "app_error.h"
#include "app_uart.h"
#include "boards.h"
#include "bsp.h"
#include "nrf.h"
#elif defined(LoggerSegger)
#include "SEGGER_RTT.h"
#elif defined(LoggerDesktop)
#include <cstdio>
#include <fmt/color.h>
#include <fmt/core.h>
#if defined USE_MSVC_DEBUG_OUT
#include <Windows.h>
#endif

#endif

namespace
{
std::string_view CaretReset = "\r\n";

constexpr const char* const severityToString(LogSeverity severity)
{
    switch (severity)
    {

    case LogSeverity::Trace:
        return "[TRACE]";
    case LogSeverity::Debug:
        return "[DEBUG]";
    case LogSeverity::Info:
        return "[INFO]";
    case LogSeverity::Warn:
        return "[WARN]";
    case LogSeverity::Error:
        return "[ERROR]";
    default:
        return "";
    }
}
} // namespace

#if defined(LoggerUart)

class Logger::LoggerImpl
{

public:
    LoggerImpl() noexcept
    {
        initLogInterface();
    }

    void logString(std::string_view _toLog) const noexcept
    {
        for (const auto ch : _toLog)
            app_uart_put(static_cast<std::uint8_t>(ch));
    }

private:
    void initLogInterface() noexcept
    {
        std::uint32_t errorCode{};

        const app_uart_comm_params_t appUartParams = {
            RX_PIN_NUMBER,
            TX_PIN_NUMBER,
            RTS_PIN_NUMBER,
            CTS_PIN_NUMBER,
            APP_UART_FLOW_CONTROL_DISABLED,
            false,
            UART_BAUDRATE_BAUDRATE_Baud115200};

        auto uartEventCallback = cbc::obtain_connector(
            [this](app_uart_evt_t* _pEvent) { return uartEventHandler(_pEvent); });

        APP_UART_FIFO_INIT(
            &appUartParams, RxSize, TxSize, uartEventCallback, APP_IRQ_PRIORITY_LOWEST, errorCode);

        APP_ERROR_CHECK(errorCode);
    }

private:
    static constexpr std::uint16_t TxSize = 256;    /**< UART TX buffer size. */
    static constexpr std::uint16_t RxSize = TxSize; /**< UART RX buffer size. */
    static constexpr std::uint8_t TestDataBytes =
        15; /**< max number of test bytes to be used for tx and rx. */

    void uartEventHandler(app_uart_evt_t* _pEvent) noexcept
    {
        if (_pEvent->evt_type == APP_UART_COMMUNICATION_ERROR)
        {
            APP_ERROR_HANDLER(_pEvent->data.error_communication);
        }
        else if (_pEvent->evt_type == APP_UART_FIFO_ERROR)
        {
            APP_ERROR_HANDLER(_pEvent->data.error_code);
        }
    }
};
#endif

#if defined(LoggerSwo)
class Logger::LoggerImpl
{

public:
    LoggerImpl() noexcept
    {
        initLogInterface();
    }

public:
    void logString(std::string_view _toLog) const noexcept
    {
        for (const auto ch : _toLog)
            ITM_SendChar(ch);
    }

private:
    void initLogInterface() noexcept
    {
        NRF_CLOCK->TRACECONFIG =
            (NRF_CLOCK->TRACECONFIG & ~CLOCK_TRACECONFIG_TRACEPORTSPEED_Msk) |
            (CLOCK_TRACECONFIG_TRACEPORTSPEED_4MHz << CLOCK_TRACECONFIG_TRACEPORTSPEED_Pos);

        ITM->TCR |= 1;
        ITM->TER |= 1;
    }
};
#endif

#if defined(LoggerSegger)
class Logger::LoggerImpl
{

public:
    LoggerImpl()
    {
        SEGGER_RTT_ConfigUpBuffer(
            0,
            "SEGGER_MAIN_BUFFER",
            seggerBuffer.data(),
            kSeggerBufferSize,
            SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL);
    }

    auto formatMessage(std::span<char> formatBuffer, LogSeverity severity, std::string_view _toLog)
        const noexcept
    {
        switch (severity)
        {
        case LogSeverity::Trace:
            return fmt::format_to_n(
                formatBuffer.data(),
                formatBuffer.size(),
                "{} {} {}\n",
                RTT_CTRL_TEXT_WHITE,
                severityToString(severity),
                _toLog.data());
            break;
        case LogSeverity::Debug:
            return fmt::format_to_n(
                formatBuffer.data(),
                formatBuffer.size(),
                "{} {} {}\n",
                RTT_CTRL_TEXT_BRIGHT_WHITE,
                severityToString(severity),
                _toLog.data());
            break;
        case LogSeverity::Info:
            return fmt::format_to_n(
                formatBuffer.data(),
                formatBuffer.size(),
                "{} {} {}\n",
                RTT_CTRL_TEXT_MAGENTA,
                severityToString(severity),
                _toLog.data());
            break;
        case LogSeverity::Warn:
            return fmt::format_to_n(
                formatBuffer.data(),
                formatBuffer.size(),
                "{} {} {}\n",
                RTT_CTRL_TEXT_BRIGHT_YELLOW,
                severityToString(severity),
                _toLog.data());
            break;
        case LogSeverity::Error:
            return fmt::format_to_n(
                formatBuffer.data(),
                formatBuffer.size(),
                "{} {} {}\n",
                RTT_CTRL_TEXT_BRIGHT_RED,
                severityToString(severity),
                _toLog.data());
            break;
        case LogSeverity::None:
            break;
        default:
            break;
        }

        std::terminate();
    }
    void logString(LogSeverity severity, std::string_view _toLog) const noexcept
    {
        std::array<char, 1024> formatBuffer{};
        auto formatResult = formatMessage(
            std::span(formatBuffer.data(), formatBuffer.size() - 1), severity, _toLog);
        formatBuffer[formatResult.size + 1] = '\0';
        auto formatString =
            std::string_view(formatBuffer.data(), formatBuffer.data() + formatResult.size + 1);

        SEGGER_RTT_Write(0, formatString.data(), formatString.size());
    }

    void completeMessage()
    {
    }
    static constexpr inline std::uint16_t kSeggerBufferSize = 512;
    static inline std::array<std::uint8_t, kSeggerBufferSize> seggerBuffer{};
};
#endif

#if defined(LoggerDesktop)
class Logger::LoggerImpl
{

public:
    void logString(LogSeverity severity, std::string_view _toLog) const noexcept
    {

        switch (severity)
        {
        case LogSeverity::Trace:
            fmt::print(
                fg(fmt::color::white_smoke), "{} {}\n", severityToString(severity), _toLog.data());
            break;
        case LogSeverity::Debug:
            fmt::print(fg(fmt::color::white), "{} {}\n", severityToString(severity), _toLog.data());
            break;
        case LogSeverity::Info:
            fmt::print(fg(fmt::color::blue), "{} {}\n", severityToString(severity), _toLog.data());
            break;
        case LogSeverity::Warn:
            fmt::print(
                fg(fmt::color::yellow), "{} {}\n", severityToString(severity), _toLog.data());
            break;
        case LogSeverity::Error:
            fmt::print(fg(fmt::color::red), "{} {}\n", severityToString(severity), _toLog.data());
            break;
        case LogSeverity::None:
            break;
        default:
            break;
        }
#if defined USE_MSVC_DEBUG_OUT
        OutputDebugString(_toLog.data());
#endif
    }
};
#endif

Logger::Logger() noexcept = default;

Logger::~Logger() = default;

Logger& Logger::Instance() noexcept
{
    static Logger intance;
    return intance;
}

void Logger::logDebugImpl(LogSeverity severity, std::string_view _toLog) noexcept
{
    m_pLoggerImpl->logString(severity, _toLog);
}