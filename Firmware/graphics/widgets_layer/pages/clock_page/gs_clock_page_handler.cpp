#include "gs_clock_page_handler.hpp"

#include "ih/gs_events.hpp"
#include "ih/pages/gs_iclock_page_view.hpp"

#include "utils/MetaUtils.hpp"

#include <charconv>

namespace Graphics::Views
{

ClockPageHandler::ClockPageHandler( IClockWatchPage* _clockPageView )
    :   m_forceUpdateAfterVisibilityChange{true}
    ,   m_pClockWatchView{ _clockPageView }
    ,   m_lastReceivedTime{ std::tm{} }
{
}

void
ClockPageHandler::handleEventImpl( const Events::TDateTimeEvents& _event, const std::any& _eventData )
{

    if( _event != Events::TDateTimeEvents::DateTimeChanged )
        return;

    TimeWrapper newDateTime { std::any_cast<TimeWrapper>( _eventData) };

    auto pClockView { m_pClockWatchView };
    if (!pClockView)
        return;

    if (!pClockView->isVisible())
    {
        m_forceUpdateAfterVisibilityChange = true;
        return;
    }

    if( newDateTime.getSeconds() != m_lastReceivedTime.getSeconds() || m_forceUpdateAfterVisibilityChange)
        pClockView->setSeconds(
            formatDoubleDigitsNumber(
                    static_cast<std::uint8_t>( newDateTime.getSeconds().count() )
                )
        );

    if( newDateTime.getMinutes() != m_lastReceivedTime.getMinutes() || m_forceUpdateAfterVisibilityChange)
        pClockView->setMinutes(
            formatDoubleDigitsNumber(
                static_cast<std::uint8_t>( newDateTime.getMinutes().count() )
            )
        );

    if( newDateTime.getHours() != m_lastReceivedTime.getHours() || m_forceUpdateAfterVisibilityChange)
        pClockView->setHours(
            formatDoubleDigitsNumber(
                static_cast<std::uint8_t>( newDateTime.getHours().count() )
            )
        );

    if( newDateTime.getWeekDayString() != m_lastReceivedTime.getWeekDayString() || m_forceUpdateAfterVisibilityChange)
        pClockView->setWeekday( newDateTime.getWeekDayString() );

    const bool bShouldApplyNewDate{
            m_lastReceivedTime.getWeekday() != newDateTime.getWeekday()
        ||  m_lastReceivedTime.getMonth() != newDateTime.getMonth()
        ||  m_lastReceivedTime.getYear() != newDateTime.getYear()
        ||  m_forceUpdateAfterVisibilityChange
    };

    if( bShouldApplyNewDate )
    {
        m_fullDateString = ClockPageHandler::formatToFullDate( newDateTime );
        pClockView->setFullDate( m_fullDateString );
    }

    m_forceUpdateAfterVisibilityChange = false;
    m_lastReceivedTime = newDateTime;
}

bool ClockPageHandler::shouldApplyNewDate(const TimeWrapper& _toCheck)
{
    return	_toCheck.getWeekday() != m_lastReceivedTime.getWeekday()
        || _toCheck.getMonthDay() != m_lastReceivedTime.getMonthDay()
        ||	_toCheck.getYear() != m_lastReceivedTime.getYear();
}

std::string
Graphics::Views::ClockPageHandler::formatToFullDate( const TimeWrapper& _toFormat )
{
    constexpr std::uint8_t arraySize = 5;
    std::array<char, arraySize> tempStr{};

    auto fastConvert = [&tempStr]( std::uint16_t _value )
    {
        auto [p, ec] = std::to_chars(
                tempStr.data()
            ,   tempStr.data() + tempStr.size()
            ,   _value
        );

        return std::string_view( tempStr.data(), p - tempStr.data() );
    };

    std::string toReturn{ _toFormat.getMonthString() };
    toReturn += '/';
    toReturn += fastConvert( _toFormat.getMonthDay() );
    toReturn += '/';
    toReturn += fastConvert( _toFormat.getYear() );

    return toReturn;
}

std::string ClockPageHandler::formatDoubleDigitsNumber(std::uint8_t _toFormat)
{
    constexpr std::uint8_t arraySize = 4;
    std::array<char, arraySize> tempStr{};

    auto [p, ec] = std::to_chars(
            tempStr.data()
        ,   tempStr.data() + tempStr.size()
        ,   _toFormat
    );

    auto digits = std::string_view( tempStr.data(), p - tempStr.data() );

    if( _toFormat < 10 )
        return "0" + std::string( digits.data() );
    return std::string( digits.data() );
}

std::unique_ptr<Graphics::IEventHandler>
createPageWatchHandler( IClockWatchPage* _clockPage )
{
    return std::make_unique<ClockPageHandler>( _clockPage );
}
}
