#include "gs_event_dispatcher.hpp"

namespace Graphics::Events
{

void EventDispatcher::subscribe( EventGroup _eventGroup, const TEventHandler& _handler )
{
    if( auto it = m_eventsMap.find( _eventGroup ); it != m_eventsMap.end() )
    {
        it->second.emplace_back( _handler );
    }
    else{
        m_eventsMap.insert( { _eventGroup, { _handler } } );
    }
}

void EventDispatcher::postEvent(TEvent &&_eventToProcess)
{
    m_eventsQueue.push_back( std::move( _eventToProcess ) );
}

void EventDispatcher::processEventQueue()
{
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
}

std::unique_ptr<EventDispatcher> createEventDispatcher()
{
    return std::make_unique<EventDispatcher>();
}

}
