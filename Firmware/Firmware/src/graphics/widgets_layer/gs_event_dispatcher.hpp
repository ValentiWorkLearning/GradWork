#pragma once

#include "gs_events.hpp"

#include <any>
#include <functional>
#include <vector>
#include <memory>
#include <atomic>

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

    std::vector<std::pair<EventGroup,SubscriberStorage>> m_eventsMap;
    std::vector<TEvent> m_eventsQueue;

    std::atomic_flag locker = ATOMIC_FLAG_INIT;
};

std::unique_ptr<EventDispatcher> createEventDispatcher();

}
