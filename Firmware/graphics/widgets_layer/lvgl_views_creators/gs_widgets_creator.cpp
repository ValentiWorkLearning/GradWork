#include "gs_widgets_creator.hpp"

#include "widgets_layer/widgets/battery/gs_battery_widget.hpp"

#include "widgets_layer/widgets/pages_switch/gs_pages_switch.hpp"

#include "widgets_layer/widgets/bluetooth/gs_bluetooth_widget.hpp"

namespace Graphics::Widgets
{
LvglWidgetsCreator::~LvglWidgetsCreator() = default;
 
std::unique_ptr<Graphics::Widgets::IBluetoothWidget>
LvglWidgetsCreator::createBluetoothWidget(Theme::IThemeController* _pThemeController)
{
	return Widgets::createBluetoothWidget(_pThemeController);
}

std::unique_ptr<Graphics::Widgets::IPagesSwitch>
LvglWidgetsCreator::createPagesSwitchWidget(Theme::IThemeController* _pThemeController)
{
	return Widgets::createPagesSwitch(_pThemeController);
}

std::unique_ptr<Graphics::Widgets::IBatteryWidget>
LvglWidgetsCreator::createBatteryWidget(Theme::IThemeController* _pThemeController)
{
	return Widgets::createBatteryWidget(_pThemeController);
}

IWidgetsCreator::Ptr createLvglWidgetsCreator()
{
	return std::make_unique<LvglWidgetsCreator>();
}

}