#pragma once

#include "ih/gs_iwidget_object.hpp"

namespace Graphics::Widgets
{

class BatteryWidget
    :   public IWidgetObject
{

public:

    ~BatteryWidget() override = default;

public:

    void show();

    void hide();

    void handleEvent( const EventDispatcher::Events::Event& _tEvent ) override;

private:
    // list of an lvgl widgets
};

};