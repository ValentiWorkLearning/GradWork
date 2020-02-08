#pragma once

#include "gs_events.hpp"

#include <any>
#include <functional>
#include <deque>
#include <unordered_map>
#include <memory>

#include "gs_events.hpp"
#include "Noncopyable.hpp"

namespace Graphics::Events
{

class EventDispatcher
    :   private Utils::noncopyable
{

public:

    using TEventHandler = std::function<void( const TEvent& )>;
    using SubscriberStorage = std::vector<TEventHandler>;

    void subscribe( EventGroup _eventGroup, const TEventHandler& _handler );
 
    void postEvent( TEvent&& _eventToProcess );

    void processEventQueue();

private:

    std::unordered_map<EventGroup,SubscriberStorage> m_eventsMap;
    std::deque<TEvent> m_eventsQueue;
};

std::unique_ptr<EventDispatcher> createEventDispatcher();

}
