#pragma once

#include "gs_ibattery_widget.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

#include <memory>

namespace Graphics::Widgets
{

class IWidgetEventHandler;

class BatteryWidget
    :   public IBatteryWidget
{

public:

    ~BatteryWidget() override = default;

public:

    void show() override ;

    void hide() override;

    void setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel ) override;

    void setBatteryStatus( BatteryStatus _iconToSet ) override;

private:
    // list of an lvgl widgets
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pBatteryIcon;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pBatteryLabel;
    // widgetVC
};

std::shared_ptr<IBatteryWidget> createBatteryWidget();

};
