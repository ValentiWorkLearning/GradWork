#pragma once

#include "ih/gs_ievent_handler.hpp"

#include "widgets_layer/gs_event_handler_base.hpp"

#include <memory>

namespace Graphics::Widgets
{

class IBatteryWidget;

class BatteryWidgetHandler
    : public Events::EventHandler<Graphics::IEventHandler, Events::TBatteryEvents>
{

public:
    explicit BatteryWidgetHandler(IBatteryWidget* _bateryWidget) noexcept;

    ~BatteryWidgetHandler() override = default;

protected:
    void handleEventImpl(const Events::TBatteryEvents& _event, const std::any& _eventData) noexcept
        override;

private:
    IBatteryWidget* m_pBatteryWidget;
};

std::unique_ptr<Graphics::IEventHandler> createBatteryWidgetHandler(IBatteryWidget*) noexcept;

}; // namespace Graphics::Widgets
