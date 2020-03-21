#pragma once

#include "ih/gs_ievent_handler.hpp"
#include <memory>

namespace Graphics::Widgets
{

class IBatteryWidget;

class BatteryWidgetHandler
    :   public Graphics::IEventHandler
{

public:

    explicit BatteryWidgetHandler( IBatteryWidget* _bateryWidget );

    ~BatteryWidgetHandler() override = default;

public:

    void handleEvent( const Events::TEvent& _event ) override;

private:

    IBatteryWidget* m_pBatteryWidget;
};

std::unique_ptr<Graphics::IEventHandler>
createBatteryWidgetHandler( IBatteryWidget* );

};
