#pragma once

#include "ih/gs_iwidget_object.hpp"

#include <memory>

namespace Graphics::Widgets
{
    class IBluetoothWidget;
    class IPagesSwitch;
    class IBatteryWidget;
}

namespace Graphics::Widgets
{
class IWidgetsCreator
{
   public:
    using Ptr = std::unique_ptr<IWidgetsCreator>;

    [[nodiscard]] virtual std::unique_ptr<Graphics::Widgets::IBluetoothWidget>
    createBluetoothWidget(Theme::IThemeController* _pThemeController) = 0;

    [[nodiscard]] virtual std::unique_ptr<Graphics::Widgets::IPagesSwitch>
    createPagesSwitchWidget(Theme::IThemeController* _pThemeController) = 0;

    [[nodiscard]] virtual std::unique_ptr<Graphics::Widgets::IBatteryWidget>
    createBatteryWidget(Theme::IThemeController* _pThemeController) = 0;

    virtual ~IWidgetsCreator() = default;
};

}