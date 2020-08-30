#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

#include <string_view>
#include <memory>
#include <charconv>
#include <atomic>

#define ENABLE_DEBUG_LOGGING
#ifdef ENABLE_DEBUG_LOGGING
    #define LOG_DEBUG(ARGS)( Logger::Instance().logDebug( ARGS ) )
    #define LOG_DEBUG_ENDL( ARGS )( Logger::Instance().logDebugEndl( ARGS ) )
#else
    #define LOG_DEBUG(ARGS)
    #define LOG_DEBUG_ENDL(ARGS)
#endif

class Logger
{

public:

    static Logger& Instance();

    void logDebugEndl( std::string_view _toLog );

    void logDebug( std::string_view _toLog );

    template< typename TToLog >
    static constexpr bool IsStringType()
    {
        using TClearType = typename std::decay<TToLog>::type;
        constexpr bool isStringType = std::is_same_v<TClearType,std::string >
                ||  std::is_same_v<TClearType,std::string_view >
                ||  std::is_same_v<TClearType,const char *>
                || std::is_same_v<TClearType, char*>;

        return isStringType;
    }

    template< typename TToLog >
    static constexpr bool IsCharType()
    {
        using TClearType = typename std::decay<TToLog>::type;
        constexpr bool isCharType = std::is_same_v<TClearType, std::uint8_t>
            || std::is_same_v<TClearType, char>
            || std::is_same_v<TClearType, unsigned char>;
        return isCharType;
    }

    template< typename TToLog >
    void logDebugEndl( const TToLog& _toLog )
    {

        constexpr bool isString = IsStringType<TToLog>();
        if constexpr ( !isString )
        {
            std::array<char, sizeof (TToLog)* 8> str{};
            if( auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(), _toLog); ec == std::errc() )
            {
                logDebugEndl( std::string_view( str.data(), p - str.data() ) );
            }
        }
        else{
            if constexpr( IsCharType<TToLog>() )
                logDebugEndl( static_cast<std::int16_t>( _toLog ) );
            else
                logDebugEndl( static_cast<std::string_view>( _toLog ) );
        }

    }

    template< typename TToLog>
    void logDebug( const TToLog& _toLog )
    {
        constexpr bool isString = IsStringType<TToLog>();
        if constexpr (!isString)
        {
            std::array<char, sizeof (TToLog)* 8> str{};
            if( auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(),_toLog); ec == std::errc() )
            {
                logDebug( std::string_view( str.data(), p - str.data() ) );
            }
        }
        else{
            if constexpr ( IsCharType<TToLog>() )
                logDebug( static_cast<std::int16_t>( _toLog ) );
            else
                logDebug( static_cast<std::string_view>( _toLog ) );
        }
    }

    template< typename TArrayType, size_t ArraySize>
    void logDebug( const std::array<TArrayType,ArraySize>& _arrayToLog )
    {
        for( auto arrayItem: _arrayToLog )
        {
            logDebug('[');
            logDebug(arrayItem);
            logDebug(']');
        }
    }

    template< typename TArrayType, size_t ArraySize>
    void logDebugEndl( const std::array<TArrayType,ArraySize>& _arrayToLog )
    {
        logDebug(_arrayToLog);
        logDebug('\n');
    }
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
