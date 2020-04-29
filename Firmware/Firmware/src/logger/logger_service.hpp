#pragma once
#include <string_view>
#include <memory>
#include <charconv>
#include <atomic>

#include "FastPimpl.hpp"
#include "Platform.hpp"

class Logger
{

public:

    static Logger& Instance();

    void logDebugEndl( std::string_view _toLog );

    void logDebug( std::string_view _toLog );

private:

    Logger();
    ~Logger();

private:

    static constexpr inline  std::size_t kImplSize =  Platform::LogerImplSize;
    static constexpr inline  std::size_t kImplAlignment = Platform::LogerImplAlignment;

private:

    mutable std::atomic_flag m_loggerReady;

    class LoggerImpl;
    Utils::FastPimpl<LoggerImpl,kImplSize,kImplAlignment> m_pLoggerImpl;
};