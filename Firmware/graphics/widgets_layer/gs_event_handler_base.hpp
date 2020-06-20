#pragma once
//Thanks, stivius9 for the idea!

#include "ih/gs_events.hpp"
#include "utils/MetaUtils.hpp"

namespace Graphics::Events
{

template <typename HeadEvent, typename... Events>
class Helper : public Helper<Events...>
{
protected:
    virtual void handleEventImpl( const HeadEvent& _eventToHandle, const std::any& _eventData) = 0;
};

template<typename HeadEvent>
class Helper< HeadEvent>
{

protected:

    virtual void handleEventImpl( const HeadEvent& _eventToHandle, const std::any& _eventData) = 0;
};


template <typename InterfaceBase, typename... TEventPack>
class EventHandler
    :   public InterfaceBase
    ,   public Helper<TEventPack...>
{
public:

    void handleEvent(const Events::TEvent& genericEvent)
    {
        switch (genericEvent.eventGroup)
        {
        case Events::EventGroup::Battery:
            if constexpr ( Meta::HasType<Events::TBatteryEvents,EventsToHandle>::value )
                this->handleEventImpl( std::any_cast<Events::TBatteryEvents>( genericEvent.eventType ), genericEvent.eventData );
            break;

        case Events::EventGroup::Heartrate:
            if constexpr ( Meta::HasType<Events::THeartRateEvents,EventsToHandle>::value )
                this->handleEventImpl( std::any_cast<Events::THeartRateEvents>( genericEvent.eventType ), genericEvent.eventData );
            break;

        case Events::EventGroup::BleDevice:
            if constexpr ( Meta::HasType<Events::TBleClientEvents,EventsToHandle>::value )
                this->handleEventImpl( std::any_cast<Events::TBleClientEvents>( genericEvent.eventType ), genericEvent.eventData );
            break;

        case Events::EventGroup::DateTime:
            if constexpr ( Meta::HasType<Events::TDateTimeEvents,EventsToHandle>::value )
                this->handleEventImpl( std::any_cast<Events::TDateTimeEvents>( genericEvent.eventType ), genericEvent.eventData );
            break;

        case Events::EventGroup::GraphicsEvents:
            if constexpr ( Meta::HasType<Events::TGraphicsEvents,EventsToHandle>::value )
                this->handleEventImpl( std::any_cast<Events::TGraphicsEvents>( genericEvent.eventType ), genericEvent.eventData );
            break;

        default:
            break;
        }
    }

private:
    using EventsToHandle = Meta::TypeList<TEventPack ... >;
};

}