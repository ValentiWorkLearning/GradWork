#pragma once

#include "ih/creators/gs_iwidgets_creator.hpp"

namespace Graphics::Widgets
{

class LvglWidgetsCreator
    :   public IWidgetsCreator
{
public:

    ~LvglWidgetsCreator() override;

public:

    std::unique_ptr<Graphics::Widgets::IBluetoothWidget>
        createBluetoothWidget(Theme::IThemeController* _pThemeController)noexcept override;

    std::unique_ptr<Graphics::Widgets::IPagesSwitch>
        createPagesSwitchWidget(Theme::IThemeController* _pThemeController)noexcept override;

    std::unique_ptr<Graphics::Widgets::IBatteryWidget>
        createBatteryWidget(Theme::IThemeController* _pThemeController)noexcept override;
};

IWidgetsCreator::Ptr createLvglWidgetsCreator()noexcept;

}