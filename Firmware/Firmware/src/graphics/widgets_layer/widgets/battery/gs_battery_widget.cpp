#include "gs_battery_widget.hpp"
#include "gs_events.hpp"

namespace Graphics::Widgets
{

void BatteryWidget::show()
{
}

void BatteryWidget::setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel )
{

}

void BatteryWidget::setBatteryStatus( BatteryStatus _iconToSet )
{

}


void BatteryWidget::hide()
{
}

std::shared_ptr<IBatteryWidget> createBatteryWidget()
{
    return std::make_shared<BatteryWidget>();
}


};
