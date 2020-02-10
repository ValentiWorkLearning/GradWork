#pragma once

#include "gs_ibattery_widget.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

#include <string>
#include <memory>

namespace Graphics::Theme
{
    class IThemeController;
}

namespace Graphics::Widgets
{

class IWidgetEventHandler;

class BatteryWidget
    :   public IBatteryWidget
{

public:

    explicit BatteryWidget( std::weak_ptr<Theme::IThemeController> _themeController );

    ~BatteryWidget() override = default;

public:

    void show() override ;

    void hide() override;

    void setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel ) override;

    void setBatteryStatus( BatteryStatus _iconToSet ) override;

private:

    void initBatteryPercentageLabel();

    void initBatteryIcon();

private:

    lv_style_t m_bateryIconStyle;
    lv_style_t m_batteryLabelStyle;

    std::string m_labelText;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pBatteryIcon;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pBatteryLabel;

    std::weak_ptr<Theme::IThemeController> m_pThemeController;

};

std::shared_ptr<IBatteryWidget> createBatteryWidget(
    std::weak_ptr<Theme::IThemeController> _themeController
);

};
