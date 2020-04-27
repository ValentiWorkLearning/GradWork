#pragma once

#include "gs_ibattery_widget.hpp"
#include "gs_widget_base_obj.hpp"

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
    :   public WidgetBaseObj<IBatteryWidget>
{

public:

    explicit BatteryWidget( const Theme::IThemeController* _themeController );

    ~BatteryWidget() override = default;

public:

    void show() override;

    void hide() override;

    void reloadStyle() override;

public:

    void setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel ) override;

    void setBatteryStatus( BatteryStatus _iconToSet ) override;

private:

    void initStyles();

    void initBatteryPercentageLabel(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    void initBatteryIcon(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

private:

    lv_style_t m_bateryIconStyle;
    lv_style_t m_batteryLabelStyle;

    std::string m_labelText;

    BatteryStatus m_currentStatus;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pBatteryIcon;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pBatteryLabel;

};

std::unique_ptr<IBatteryWidget> createBatteryWidget(
   const Theme::IThemeController* _themeController
);

};
