#pragma once
#include <string_view>
#include <memory>

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

    class LoggerImpl;
    std::unique_ptr<LoggerImpl> m_pLoggerImpl;
};