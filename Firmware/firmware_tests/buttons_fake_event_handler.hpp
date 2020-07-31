#pragma once

#include "ih/gs_events.hpp"
#include "ih/gs_ievent_handler.hpp"

#include "widgets_layer/gs_event_handler_base.hpp"


namespace FakeButton
{

class FakeButtonEventsHandler
    :   public Graphics::Events::EventHandler<
            Graphics::IEventHandler
        ,   Graphics::Events::TButtonsEvents
    >
{

public:

    explicit FakeButtonEventsHandler() = default;

    ~FakeButtonEventsHandler() override = default;

protected:

    void handleEventImpl(const Graphics::Events::TButtonsEvents& _event, const std::any& _eventData) override
    {
    }

private:

    Graphics::Events::TButtonsEvents m_lastEvent;
    std::uint8_t m_button;
};

Graphics::TEventHandlerPtr createFakeButtonsHandler()
{
    return std::make_unique<FakeButtonEventsHandler>();
}

}