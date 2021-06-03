#pragma once

#include "ih/gs_events.hpp"
#include "ih/gs_ievent_handler.hpp"

#include "widgets_layer/gs_event_handler_base.hpp"

namespace FakeButton
{

class FakeButtonEventsHandler
    : public Graphics::Events::
          EventHandler<Graphics::IEventHandler, Graphics::Events::TButtonsEvents>
{

public:
    explicit FakeButtonEventsHandler() : m_button{} {};

    ~FakeButtonEventsHandler() override = default;

public:
    bool hasEvents() const
    {
        return !m_receivedEvents.empty();
    }

    size_t getEventsCount() const
    {
        return m_receivedEvents.size();
    }

    Graphics::Events::TButtonsEvents getEventAt(size_t _eventIndex)
    {
        return m_receivedEvents.at(_eventIndex);
    }

    Graphics::Events::TButtonsEvents getLastEvent() const
    {
        return m_receivedEvents.back();
    }

    Buttons::ButtonId getLastButton() const
    {
        return m_button;
    }

protected:
    void handleEventImpl(
        const Graphics::Events::TButtonsEvents& _event,
        const std::any& _eventData) noexcept override
    {
        m_receivedEvents.push_back(_event);
        m_button = std::any_cast<Buttons::ButtonId>(_eventData);
    }

private:
    using TEventsStorage = std::vector<Graphics::Events::TButtonsEvents>;
    TEventsStorage m_receivedEvents;
    Buttons::ButtonId m_button;
};

using TFakeButtonsHandlerPtr = std::unique_ptr<FakeButtonEventsHandler>;

TFakeButtonsHandlerPtr createFakeButtonsHandler() noexcept
{
    return std::make_unique<FakeButtonEventsHandler>();
}

} // namespace FakeButton