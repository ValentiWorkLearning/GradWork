#include "gs_event_dispatcher.hpp"

#include <algorithm>

namespace Graphics::Events
{

void EventDispatcher::subscribe( EventGroup _eventGroup, const TEventHandler& _handler )
{
    while ( locker.test_and_set( std::memory_order_acquire ) );

    if( auto it = m_eventsMap.find( _eventGroup ); it != m_eventsMap.end() )
    {
        it->second.emplace_back( _handler );
    }
    else{
        m_eventsMap.insert( { _eventGroup, { _handler } } );
    }

    locker.clear( std::memory_order_release );
}

void EventDispatcher::postEvent(TEvent &&_eventToProcess)
{
    while ( locker.test_and_set( std::memory_order_acquire ) );

    m_eventsQueue.push_back( std::move( _eventToProcess ) );
    locker.clear(std::memory_order_release);
}

void EventDispatcher::processEventQueue()
{
    while ( locker.test_and_set( std::memory_order_acquire ) );

    for( const auto& event : m_eventsQueue )
    {
        if( auto it = m_eventsMap.find( event.eventGroup ); it != m_eventsMap.end() )
        {
            std::for_each(
                    it->second.cbegin()
                ,   it->second.cend()
                ,   [&event]( const auto& _callback )
                    {
                        _callback( event );
                    }
            );
        }
    }
    m_eventsQueue.clear();

    locker.clear( std::memory_order_release );
}

std::unique_ptr<EventDispatcher> createEventDispatcher()
{
    return std::make_unique<EventDispatcher>();
}

}
