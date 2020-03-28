#pragma once

#include<any>
#include <type_traits>

namespace Graphics::Events
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

struct TEvent
{
    EventGroup eventGroup;
    std::any eventType;
    std::any eventData;
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

enum class TDateTimeEvents
{
        DateTimeEventsBegin = enumConvert<THeartRateEvents>( THeartRateEvents::HeartRateEventsEnd )
    ,   DateTimeChanged
    ,   DateTimeEventsEnd
};

enum class TBleClientEvents
{
        BleClientEventsBegin = enumConvert<TDateTimeEvents>( TDateTimeEvents::DateTimeEventsEnd )
    ,   DeviceConnected
    ,   DeviceDisconnected
    ,   BleClientEventsEnd
};

}
