#include "gs_clock_page_handler.hpp"

#include "ih/gs_events.hpp"

#include "gs_iclock_page_view.hpp"

namespace Graphics::Views
{

ClockPageHandler::ClockPageHandler( std::weak_ptr<IClockWatchPage> _clockPageView )
    :   m_pClockWatchView{ _clockPageView }
    ,   m_lastReceivedTime{ std::tm{} }
	,	forceUpdateAfterVisibilityChange{false}
{
}

void ClockPageHandler::handleEvent( const Events::TEvent& _event )
{
// TODO move this to baseHandler, replace to virtual functions like
// Handle BatteryEvent, Handle HeartRateEvent
// Think about metatype resistartion through using std::variant<TEvent1, TEvent2,TEvent...>
// Or fo instance consider using static visitor idiom for decalring possible visitable types like
// EventHandlerVisitor<TEvent1,TEvent2,TEvent3>

	Events::TDateTimeEvents dateTimeEvents { std::any_cast<Events::TDateTimeEvents>( _event.eventType ) };
	TimeWrapper newDateTime { std::any_cast<TimeWrapper>( _event.eventData ) };

	auto pClockView { m_pClockWatchView.lock() };
	if (!pClockView)
		return;

	if (!pClockView->isVisible())
	{
		forceUpdateAfterVisibilityChange = true;
		return;
	}

	if( newDateTime.getSeconds() != m_lastReceivedTime.getSeconds() || forceUpdateAfterVisibilityChange)
		pClockView->setSeconds(
			formatDoubleDigitsNumber(
					static_cast<std::uint8_t>( newDateTime.getSeconds().count() )
				)
		);

	if( newDateTime.getMinutes() != m_lastReceivedTime.getMinutes() || forceUpdateAfterVisibilityChange)
		pClockView->setMinutes(
			formatDoubleDigitsNumber(
				static_cast<std::uint8_t>( newDateTime.getMinutes().count() )
			)
		);

	if( newDateTime.getHours() != m_lastReceivedTime.getHours() || forceUpdateAfterVisibilityChange)
		pClockView->setHours(
			formatDoubleDigitsNumber(
				static_cast<std::uint8_t>( newDateTime.getHours().count() )
			)
		);

	bool bApplyNewDate{ shouldApplyNewDate( newDateTime ) || forceUpdateAfterVisibilityChange };

	forceUpdateAfterVisibilityChange = false;

	m_lastReceivedTime = newDateTime;

	pClockView->setWeekday( m_lastReceivedTime.getWeekDayString() );

	m_fullDateString = ClockPageHandler::formatToFullDate( m_lastReceivedTime );
	pClockView->setFullDate( m_fullDateString );

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
	std::string toReturn{ _toFormat.getMonthString() };
	toReturn += '/';
	toReturn += std::to_string( _toFormat.getMonthDay() );
	toReturn += '/';
	toReturn += std::to_string( _toFormat.getYear() );

	return toReturn;
}

std::string ClockPageHandler::formatDoubleDigitsNumber(std::uint8_t _toFormat)
{
	if( _toFormat < 10 )
		return '0' + std::to_string( _toFormat );
	return std::to_string( _toFormat );
}

std::unique_ptr<Graphics::IEventHandler>
createPageWatchHandler( std::weak_ptr<IClockWatchPage> _clockPage )
{
	return std::make_unique<ClockPageHandler>( _clockPage );
}
}
