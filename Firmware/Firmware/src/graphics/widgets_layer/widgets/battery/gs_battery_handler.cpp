#include "ih/gs_events.hpp"

#include "gs_battery_handler.hpp"


namespace Graphics::Widgets
{

BatteryWidgetHandler::BatteryWidgetHandler( std::weak_ptr<IBatteryWidget> _bateryWidget )
    :   m_pBatteryWidget{ _bateryWidget }
{

}

void BatteryWidgetHandler::handleEvent( const Events::TEvent& _event )
{

}

std::unique_ptr<Graphics::IEventHandler>
createBatteryWidgetHandler( std::weak_ptr<IBatteryWidget> _batteryWidget)
{
    return std::make_unique<BatteryWidgetHandler>( _batteryWidget );
}

}
