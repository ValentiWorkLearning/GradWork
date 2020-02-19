#include "gs_battery_handler.hpp"

#include "widgets/battery/gs_ibattery_widget.hpp"

#include "ih/gs_events.hpp"

namespace
{
	Graphics::Widgets::IBatteryWidget::BatteryStatus toBatteryStatus( std::uint8_t _batteryValue )
	{
		if( _batteryValue <= 25 )
			return Graphics::Widgets::IBatteryWidget::BatteryStatus::QuaterCharge;
		else if( _batteryValue >25 && _batteryValue <= 50 )
			return Graphics::Widgets::IBatteryWidget::BatteryStatus::HalfCharged;
		else if( _batteryValue > 50 && _batteryValue <= 75 )
			return Graphics::Widgets::IBatteryWidget::BatteryStatus::Charge75Percents;
		else if( _batteryValue > 75 && _batteryValue <= 90 )
			return Graphics::Widgets::IBatteryWidget::BatteryStatus::Charged90Percents;
		else
			return Graphics::Widgets::IBatteryWidget::BatteryStatus::FullCharged;
	}
}

namespace Graphics::Widgets
{

BatteryWidgetHandler::BatteryWidgetHandler( std::weak_ptr<IBatteryWidget> _bateryWidget )
    :   m_pBatteryWidget{ _bateryWidget }
{

}

void BatteryWidgetHandler::handleEvent( const Events::TEvent& _event )
{
	// TODO move this to baseHandler, replace to virtual functions like
	// Handle BatteryEvent, Handle HeartRateEvent
	Events::TBatteryEvents batEvents = std::any_cast<Events::TBatteryEvents>( _event.eventType );
	std::uint8_t batteryValue = std::any_cast<std::uint8_t>( _event.eventData );

	switch ( _event.eventGroup )
	{
	case Events::EventGroup::Battery:
		if( auto pBatteryWidget = m_pBatteryWidget.lock(); pBatteryWidget && pBatteryWidget->isVisible() )
		{
			pBatteryWidget->setBatteryLevelPercentage( batteryValue );
			pBatteryWidget->setBatteryStatus( toBatteryStatus( batteryValue ) );
		}
		break;
	default:
		break;
	}
}

std::unique_ptr<Graphics::IEventHandler>
createBatteryWidgetHandler( std::weak_ptr<IBatteryWidget> _batteryWidget)
{
    return std::make_unique<BatteryWidgetHandler>( _batteryWidget );
}

}
