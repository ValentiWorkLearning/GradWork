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

    explicit FakeButtonEventsHandler()
        :   m_button{}
        ,   m_lastEvent{ Graphics::Events::TButtonsEvents::TButtonsEventsBegin }
    {
    };

    ~FakeButtonEventsHandler() override = default;

public:

    Graphics::Events::TButtonsEvents getLastEvent() const
    {
        return m_lastEvent;
    }

    std::uint8_t getLastButton() const
    {
        return m_button;
    }

protected:

    void handleEventImpl(const Graphics::Events::TButtonsEvents& _event, const std::any& _eventData) override
    {
        m_lastEvent = _event;
        m_button = std::any_cast<std::uint8_t>( _eventData );
    }

private:

    Graphics::Events::TButtonsEvents m_lastEvent;
    std::uint8_t m_button;
};

using TFakeButtonsHandlerPtr = std::unique_ptr<FakeButtonEventsHandler>;

TFakeButtonsHandlerPtr createFakeButtonsHandler()
{
    return std::make_unique<FakeButtonEventsHandler>();
}

}