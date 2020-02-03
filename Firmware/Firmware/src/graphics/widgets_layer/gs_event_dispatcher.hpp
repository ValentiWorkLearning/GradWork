#pragma once

#include <any>
#include <functional>
#include <queue>
#include <unordered_map>

namespace Graphics
{

enum class EventGroup
{
        Battery
    ,   Heartrate
    ,   BleDevice
    ,   Gesture
    ,   HardwareButtons
    ,   DateTime
};

struct EventType
{
};

struct TEvent
{
    EventGroup eventGroup;
    EventType eventType;
    std::any eventData;
}

class EventDispatcher
{

public:

    using TEventHandler = std::function<void( const TEvent& )>;

    void subscribe( EventGroup, const TEventHandler& _handler );
 
    void postEvent( TEvent&& _eventToProcess );

    void processEventQueue();

private:

    void processOverlappedEvents();

private:

    std::unordered_map<EventGroup,TEventHandler> m_eventsMap;
    std::queue<TEvent> m_eventsQueue;
};

}