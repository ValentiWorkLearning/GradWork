#include "logger_service.hpp"

#include "CallbackConnector.hpp"
#include <atomic>
#include <type_traits>

#if defined(LoggerUart) 
#include "nrf.h"
#include "boards.h"
#include "app_uart.h"
#include "app_error.h"
#include "bsp.h"
#elif defined(LoggerSwo)
#include "nrf.h"
#include "boards.h"
#include "app_uart.h"
#include "app_error.h"
#include "bsp.h"
#elif defined(LoggerSegger)
#include "SEGGER_RTT.h"
#elif defined(LoggerDesktop)
#include <iostream>
#endif

class UartLogger;
class SwoLogger;
class SeggerRttLog;
class DesktopLogger;

struct LoggerImplChoise
{

#if defined (LoggerUart)
    using TLoggerImpl = UartLogger;
#elif defined(LoggerSwo)
    using TLoggerImpl = SwoLogger;
#elif defined(LoggerSegger)
    using TLoggerImpl = SeggerRttLog;
#elif defined(LoggerDesktop)
    using TLoggerImpl = DesktopLogger;
#else
    using TLoggerImpl = std::void_t<>;
#endif
};

namespace
{
    std::string_view CaretReset = "\r\n";
}

class Logger::LoggerImpl
{

public:

    template< typename TLoggerType>
    explicit LoggerImpl( TLoggerType&& _logger )
        :   m_loggerHider{ std::make_unique<LoggerTempateImpl<TLoggerType>>( std::forward<TLoggerType>( _logger ) ) }
    {
        m_loggerHider->initLogInterface();
    }

    void logDebugEndl( std::string_view _toLog )
    {
        m_loggerHider->logDebug( _toLog );
        m_loggerHider->logDebug( CaretReset );
    };

    void logDebug( std::string_view _toLog )
    {
        m_loggerHider->logDebug( _toLog );
    };


    struct ILoggerHider
    {
        virtual ~ILoggerHider() = default;

        virtual void logDebugEndl( std::string_view _toLog ) const = 0;

        virtual void logDebug( std::string_view _toLog ) const = 0;

        virtual void initLogInterface()= 0;

    };

    template< typename TLoggerHider >
    class LoggerTempateImpl
        :   public ILoggerHider
    {

    public:

        explicit LoggerTempateImpl( TLoggerHider&& _loggerConcrete )
            :   m_logger{ std::forward<TLoggerHider>( _loggerConcrete ) }
        {
        }

        void logDebugEndl( std::string_view _toLog ) const override
        {
            while ( m_loggerReady.test_and_set( std::memory_order_acquire ) )
            {
                m_logger.logString( _toLog );
                m_logger.logString( CaretReset );

                m_loggerReady.clear( std::memory_order_release );
            }
        }

        void logDebug( std::string_view _toLog ) const override
        {
            while ( m_loggerReady.test_and_set( std::memory_order_acquire ) )
            {
                m_logger.logString( _toLog );
                m_loggerReady.clear( std::memory_order_release );
            }
        }

        void initLogInterface()
        {
            while ( m_loggerReady.test_and_set( std::memory_order_acquire ) )
            {
                m_logger.initLogInterface();
                m_loggerReady.clear( std::memory_order_release );
            }
        }

        ~LoggerTempateImpl()override = default;

    private:
        mutable std::atomic_flag m_loggerReady;
        TLoggerHider m_logger;
    };

private:
    std::unique_ptr<ILoggerHider> m_loggerHider;
};

#if defined (LoggerUart)
class UartLogger
{

public:

    void initLogInterface()
    {
        std::uint32_t errorCode{};

        const app_uart_comm_params_t appUartParams =
        {
                RX_PIN_NUMBER
            ,   TX_PIN_NUMBER
            ,   RTS_PIN_NUMBER
            ,   CTS_PIN_NUMBER
            ,   APP_UART_FLOW_CONTROL_DISABLED
            ,   false
            ,   UART_BAUDRATE_BAUDRATE_Baud115200
        };

        auto uartEventCallback = cbc::obtain_connector(
            [ this ]( app_uart_evt_t * _pEvent )
            {
                return uartEventHandler( _pEvent );
            }
        );

        APP_UART_FIFO_INIT(
                &appUartParams
            ,   RxSize
            ,   TxSize
            ,   uartEventCallback
            ,   APP_IRQ_PRIORITY_LOWEST
            ,   errorCode
        );

        APP_ERROR_CHECK( errorCode );
    }

    void logString( std::string_view _toLog ) const
    {
        for( const auto ch : _toLog )
           app_uart_put( static_cast<std::uint8_t>( ch ) );
    }

private:

    static constexpr std::uint16_t TxSize = 256;        /**< UART TX buffer size. */
    static constexpr std::uint16_t RxSize = TxSize;     /**< UART RX buffer size. */
    static constexpr std::uint8_t TestDataBytes = 15;   /**< max number of test bytes to be used for tx and rx. */

    void uartEventHandler(app_uart_evt_t * _pEvent)
    {
        if (_pEvent->evt_type == APP_UART_COMMUNICATION_ERROR)
        {
            APP_ERROR_HANDLER( _pEvent->data.error_communication );
        }
        else if ( _pEvent->evt_type == APP_UART_FIFO_ERROR )
        {
            APP_ERROR_HANDLER( _pEvent->data.error_code );
        }
    }
};
#endif

#if defined (LoggerSwo)
class SwoLogger
{

public:

    void initLogInterface()
    {
        NRF_CLOCK->TRACECONFIG =
            ( NRF_CLOCK->TRACECONFIG & ~CLOCK_TRACECONFIG_TRACEPORTSPEED_Msk )
        |   ( CLOCK_TRACECONFIG_TRACEPORTSPEED_4MHz << CLOCK_TRACECONFIG_TRACEPORTSPEED_Pos );

        ITM->TCR |= 1;
        ITM->TER |= 1;
    }

    void logString( std::string_view _toLog ) const
    {
        for( const auto ch : _toLog )
            ITM_SendChar( ch );
    }
};
#endif


#if defined (LoggerSegger)
class SeggerRttLog
{

public:

    void initLogInterface()
    {

    }

    void logString( std::string_view _toLog ) const
    {
        SEGGER_RTT_WriteString( 0, _toLog.data() );
    }
};
#endif

#if defined (LoggerDesktop)
class DesktopLogger
{

public:

    void initLogInterface()
    {

    }

    void logString(std::string_view _toLog) const
    {
        std::cout << _toLog;
    }
};
#endif

Logger::Logger()
{
    static_assert(
            !std::is_same_v<LoggerImplChoise::TLoggerImpl , std::void_t<> >
        ,   "TLoggerImpl is std::void_t. Probably you forgot to choise between LoggerUart/LoggerSwo/LoggerSegger/LoggerDesktop macro"
    );

    m_pLoggerImpl = std::make_unique<LoggerImpl>(
                std::forward<LoggerImplChoise::TLoggerImpl>( LoggerImplChoise::TLoggerImpl()
            )
        );
}

Logger::~Logger() = default;

Logger& Logger::Instance()
{
    static Logger intance;
    return intance;
}

void Logger::logDebugEndl( std::string_view _toLog )
{
    m_pLoggerImpl->logDebugEndl( _toLog );
}

void Logger::logDebug( std::string_view _toLog )
{
    m_pLoggerImpl->logDebug( _toLog );
}