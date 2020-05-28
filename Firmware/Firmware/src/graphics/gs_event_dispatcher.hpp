#pragma once

#include "ih/gs_events.hpp"

#include <any>
#include <functional>
#include <vector>
#include <memory>
#include <atomic>

#include "Noncopyable.hpp"

#include <etl/vector.h>

namespace Graphics::Events
{

class EventDispatcher
    :   private Utils::noncopyable
{

public:

    using TEventHandler = std::function<void( const TEvent& )>;

    static constexpr inline int MaxSubscriberLimit = 3;
    using SubscriberStorage = etl::vector<TEventHandler,MaxSubscriberLimit>;

    void subscribe( EventGroup _eventGroup, const TEventHandler& _handler );
 
    void postEvent( TEvent&& _eventToProcess );

    void processEventQueue();

private:

    static constexpr inline int EventsCount =
        Events::enumConvert<EventGroup>( EventGroup::EventGroupEnd );
    static constexpr inline int EventPoolSize = 16;

    etl::vector<std::pair<EventGroup,SubscriberStorage>,EventsCount> m_eventsMap;
    etl::vector<TEvent,EventPoolSize> m_eventsQueue;

    std::atomic_flag locker = ATOMIC_FLAG_INIT;
};

std::unique_ptr<EventDispatcher> createEventDispatcher();

}
