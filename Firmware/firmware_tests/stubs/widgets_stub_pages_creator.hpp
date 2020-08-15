#pragma once

#include "ih/creators/gs_iwidgets_creator.hpp"

namespace Graphics::StubWidgets
{

class StubWidgetsCreator
    :   public Graphics::Widgets::IWidgetsCreator
{
public:

    ~StubWidgetsCreator() override;

public:

    std::unique_ptr<Graphics::Widgets::IBluetoothWidget>
        createBluetoothWidget(Graphics::Theme::IThemeController* _pThemeController) override;

    std::unique_ptr<Graphics::Widgets::IPagesSwitch>
        createPagesSwitchWidget(Graphics::Theme::IThemeController* _pThemeController) override;

    std::unique_ptr<Graphics::Widgets::IBatteryWidget>
        createBatteryWidget(Graphics::Theme::IThemeController* _pThemeController) override;
};

Graphics::Widgets::IWidgetsCreator::Ptr createStubWidgetsCreator();

}