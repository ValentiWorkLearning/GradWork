#include "widgets_stub_pages_creator.hpp"

#include "ih/widgets/gs_ibattery_widget.hpp"
#include "ih/widgets/gs_ibluetooth_widget.hpp"
#include "ih/widgets/gs_ipages_switch.hpp"

namespace Graphics::StubWidgets
{
StubWidgetsCreator::~StubWidgetsCreator() = default;

std::unique_ptr<Graphics::Widgets::IBluetoothWidget>
StubWidgetsCreator::createBluetoothWidget(Graphics::Theme::IThemeController * _pThemeController)
{
	return nullptr;
}
std::unique_ptr<Graphics::Widgets::IPagesSwitch> StubWidgetsCreator::createPagesSwitchWidget(Graphics::Theme::IThemeController* _pThemeController)
{
	return std::unique_ptr<Graphics::Widgets::IPagesSwitch>();
}
std::unique_ptr<Graphics::Widgets::IBatteryWidget>
StubWidgetsCreator::createBatteryWidget(Graphics::Theme::IThemeController* _pThemeController)
{
	return nullptr;
}
Graphics::Widgets::IWidgetsCreator::Ptr createStubWidgetsCreator()
{
	return std::make_unique<StubWidgetsCreator>();
}
}