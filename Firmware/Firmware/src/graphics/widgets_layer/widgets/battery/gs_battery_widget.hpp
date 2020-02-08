#pragma once

#include "gs_ibattery_widget.hpp"

#include <memory>

namespace Graphics::Widgets
{

class IWidgetEventHandler;

class BatteryWidget
    :   public IBatteryWidget
{

public:

    ~BatteryWidget() override = default;

    IEventHandler& getEventHandler() override;

    IEventHandler& getEventHandler() const override;

public:

    void show() override ;

    void hide() override;

    void setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel ) override;

    void setBatteryStatus( BatteryStatus _iconToSet ) override;

private:
    // list of an lvgl widgets

    // widgetVC
    //std::weak_ptr<IEventHandler> m_batteryWidgetHandler;
};

std::shared_ptr<IBatteryWidget> createBatteryWidget();

};
