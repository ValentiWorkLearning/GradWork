#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

#include <atomic>
#include <charconv>
#include <memory>
#include <string_view>

#if defined(USE_DEVICE_SPECIFIC)
#define FMT_HEADER_ONLY
#endif
#include <fmt/format.h>
#include <span>

enum class LogSeverity
{
    Debug,
    Info,
    Warn,
    Error
};

#define ENABLE_DEBUG_LOGGING
#ifdef ENABLE_DEBUG_LOGGING
#define LOG_DEBUG(ARGS) (Logger::Instance().logDebug(LogSeverity::Debug, ARGS))
#define LOG_INFO(ARGS) (Logger::Instance().logDebug(LogSeverity::Info, ARGS))
#define LOG_WARN(ARGS) (Logger::Instance().logDebug(LogSeverity::Warn, ARGS))
#define LOG_ERROR(ARGS) (Logger::Instance().logDebug(LogSeverity::Error, ARGS))
#else
#define LOG_DEBUG(ARGS)
#define LOG_INFO(ARGS)
#define LOG_WARN(ARGS)
#define LOG_ERROR(ARGS)
#endif

template <> struct fmt::formatter<std::span<const std::uint8_t>>
{

    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {

        auto it = ctx.begin(), end = ctx.end();

        if (it != end && *it == 'f')
        {
            ++it;
            if (it != end && *it != '}')
                std::terminate();
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const std::span<const std::uint8_t>& p, FormatContext& ctx) -> decltype(ctx.out())
    {

        auto tempFormatHolder = std::string_view{
            reinterpret_cast<const char*>(p.data()),
            reinterpret_cast<const char*>(p.data()) + p.size()};
        auto dataSize = tempFormatHolder.length();

        return format_to(ctx.out(), "{}", tempFormatHolder);
    }
};

class Logger
{

public:
    static Logger& Instance() noexcept;

    template <typename TToLog> static constexpr bool IsStringType() noexcept
    {
        using TClearType = typename std::decay<TToLog>::type;
        constexpr bool isStringType = std::is_same_v<TClearType, std::string> ||
                                      std::is_same_v<TClearType, std::string_view> ||
                                      std::is_same_v<TClearType, const char*> ||
                                      std::is_same_v<TClearType, char*>;

        return isStringType;
    }

    template <typename TToLog> static constexpr bool IsCharType() noexcept
    {
        using TClearType = typename std::decay<TToLog>::type;
        constexpr bool isCharType = std::is_same_v<TClearType, std::uint8_t> ||
                                    std::is_same_v<TClearType, char> ||
                                    std::is_same_v<TClearType, unsigned char>;
        return isCharType;
    }

    template <typename TToLog> void logDebug(LogSeverity severity, const TToLog& _toLog) noexcept
    {

        constexpr bool isString = IsStringType<TToLog>();
        if constexpr (!isString)
        {
            std::array<char, sizeof(TToLog) * 8> str{};
            if (auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(), _toLog);
                ec == std::errc())
            {
                logDebug(severity, std::string_view(str.data(), p - str.data()));
            }
        }
        else
        {
            if constexpr (IsCharType<TToLog>())
                logDebug(severity, static_cast<std::int16_t>(_toLog));
            else
                logDebug(severity, static_cast<std::string_view>(_toLog));
        }
    }

    void logDebug(LogSeverity severity, std::string_view _toLog) noexcept;

private:
    Logger() noexcept;
    ~Logger();

private:
    static constexpr inline std::size_t kImplSize = Platform::LogerImplSize;
    static constexpr inline std::size_t kImplAlignment = Platform::LogerImplAlignment;

private:
    mutable std::atomic_flag m_loggerReady;

    class LoggerImpl;
    Utils::FastPimpl<LoggerImpl, kImplSize, kImplAlignment> m_pLoggerImpl;
};
