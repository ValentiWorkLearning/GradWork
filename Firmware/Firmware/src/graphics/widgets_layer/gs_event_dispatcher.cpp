#include "gs_event_dispatcher.hpp"

#include <algorithm>

namespace Graphics::Events
{

void EventDispatcher::subscribe( EventGroup _eventGroup, const TEventHandler& _handler )
{
    while ( locker.test_and_set( std::memory_order_acquire ) );

    auto it = std::find_if(
            m_eventsMap.begin()
        ,   m_eventsMap.end()
        ,   [_eventGroup]( const auto& _toCompare )
        {
            const auto& [event, storage] = _toCompare;
            return _eventGroup == event;
        }
    );

    if( it != m_eventsMap.end() )
    {
        it->second.emplace_back( _handler );
    }
    else{
        m_eventsMap.push_back( { _eventGroup, { _handler } } );
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
        auto it = std::find_if(
                m_eventsMap.begin()
            ,   m_eventsMap.end()
            ,   [eventGroup = event.eventGroup]( const auto& _toCompare )
            {
                const auto& [event, storage] = _toCompare;
                return eventGroup == event;
            }
        );
        if( it != m_eventsMap.end() )
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
