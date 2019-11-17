#include "logger_service.hpp"

#include "app_uart.h"
#include "app_error.h"
#include "bsp.h"

#include "nrf.h"
#include "boards.h"

#include "CallbackConnector.hpp"

#include <type_traits>


class Logger::LoggerImpl
{

public:

    template< typename TLoggerType>
    LoggerImpl( TLoggerType&& _logger )
        :   m_loggerHider{ std::make_unique<LoggerTempateImpl<TLoggerType>>( std::forward<TLoggerType>( _logger ) ) }
    {
        m_loggerHider->initLogInterface();
    }

    void logDebug( std::string_view _toLog )
    {
        m_loggerHider->logString( _toLog );
    };


    struct ILoggerHider
    {
        virtual ~ILoggerHider() = default;

        virtual void logString( std::string_view _toLog ) const = 0;

        virtual void initLogInterface()= 0;

    };

    template< typename TLoggerHider >
    class LoggerTempateImpl
        :   public ILoggerHider
    {

    public:

        LoggerTempateImpl( TLoggerHider&& _loggerConcrete )
            :   m_logger{ std::forward<TLoggerHider>( _loggerConcrete ) }
        {
        }

        void logString( std::string_view _toLog ) const override
        {
            m_logger.logString( _toLog );
        }

        void initLogInterface()
        {
            m_logger.initLogInterface();
        }

        ~LoggerTempateImpl()override = default;

    private:
        TLoggerHider m_logger;
    };

private:
    std::unique_ptr<ILoggerHider> m_loggerHider;
};

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

struct LoggerImplChoise
{

#if defined (LoggerUart)
    using TLoggerImpl = UartLogger;
#elif defined(LoggerSwo)
    using TLoggerImpl = SwoLogger;
#else
    using TLoggerImpl = std::void_t<>;
#endif

};

Logger::Logger()
{
    static_assert(
            !std::is_same_v<LoggerImplChoise::TLoggerImpl , std::void_t<> >
        ,   "TLoggerImpl is std::void_t. Probably you forgot to choise between LoggerUart or LoggerSwo macro"
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

void Logger::logDebug( std::string_view _toLog )
{
    m_pLoggerImpl->logDebug( _toLog );
}