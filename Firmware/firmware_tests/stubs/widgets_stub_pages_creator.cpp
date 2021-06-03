#include "widgets_stub_pages_creator.hpp"

#include "battery_widget_fake.hpp"
#include "bluetooth_widget_fake.hpp"
#include "pages_switch_widget_fake.hpp"

namespace Graphics::StubWidgets
{
StubWidgetsCreator::~StubWidgetsCreator() = default;

std::unique_ptr<Graphics::Widgets::IBluetoothWidget> StubWidgetsCreator::createBluetoothWidget(
    Graphics::Theme::IThemeController* _pThemeController) noexcept
{
    return std::make_unique<BluetoothWidgetStub>();
}
std::unique_ptr<Graphics::Widgets::IPagesSwitch> StubWidgetsCreator::createPagesSwitchWidget(
    Graphics::Theme::IThemeController* _pThemeController) noexcept
{
    return std::make_unique<PagesSwitchWidgetStub>();
}
std::unique_ptr<Graphics::Widgets::IBatteryWidget> StubWidgetsCreator::createBatteryWidget(
    Graphics::Theme::IThemeController* _pThemeController) noexcept
{
    return std::make_unique<BatteryWidgetStub>();
}
Graphics::Widgets::IWidgetsCreator::Ptr createStubWidgetsCreator() noexcept
{
    return std::make_unique<StubWidgetsCreator>();
}
} // namespace Graphics::StubWidgets