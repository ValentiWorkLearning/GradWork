#include "gs_event_dispatcher.hpp"

#include <algorithm>

namespace Graphics::Events
{

void EventDispatcher::subscribe( EventGroup _eventGroup, const TEventHandler& _handler )noexcept
{
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

}

void EventDispatcher::postEvent(TEvent &&_eventToProcess)noexcept
{
    m_eventsQueue.push( std::move( _eventToProcess ) );
}

void EventDispatcher::processEventQueue()noexcept
{
    TEvent tempEvent{};
    while( m_eventsQueue.pop(tempEvent) )
    {
        auto it = std::find_if(
                m_eventsMap.begin()
            ,   m_eventsMap.end()
            ,   [eventGroup = tempEvent.eventGroup](const auto& _toCompare)
        {
            const auto& [event, storage] = _toCompare;
            return eventGroup == event;
        }
        );
        if (it != m_eventsMap.end())
        {
            std::for_each(
                    it->second.cbegin()
                ,   it->second.cend()
                ,   [tempEvent](const auto& _callback)
            {
                _callback(tempEvent);
            }
            );
        }
    }
}

std::unique_ptr<EventDispatcher> createEventDispatcher()
{
    return std::make_unique<EventDispatcher>();
}

}
