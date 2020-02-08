#pragma once

#include<any>
#include <type_traits>

namespace Graphics::Events
{

enum class EventGroup;

struct TEvent
{
    EventGroup eventGroup;
    std::any eventType;
    std::any eventData;
};

enum class EventGroup
{
        Battery
    ,   Heartrate
    ,   BleDevice
    ,   Gesture
    ,   HardwareButtons
    ,   DateTime
};

enum class TEventKind
{
    EventBegin
};

template <typename TEnumToApply, typename TToConvert >
constexpr auto enumConvert( TToConvert _valueToConvert )
{
    return static_cast<typename std::underlying_type<TEnumToApply>::type>( _valueToConvert );
}

enum class TBatteryEvents
{
        BatteryEventsStart = enumConvert<TEventKind>(TEventKind::EventBegin)
    ,   BatteryLevelChanged
    ,   BatteryEventsEnd
};

enum class THeartRateEvents
{
        HeartRateEventsBegin = enumConvert<TBatteryEvents>( TBatteryEvents::BatteryEventsEnd )
    ,   MeasureStarted
    ,   MeasureCompleted
    ,   MeasureFailed
    ,   HeartRateEventsEnd
};

}