#pragma once

#include <any>
#include <cstdint>
#include <type_traits>

namespace Graphics::Events
{

enum class EventGroup : std::uint8_t
{
    Battery,
    Heartrate,
    BleDevice,
    Gesture,
    HardwareButtons,
    DateTime,
    GraphicsEvents,
    Buttons,
    EventGroupEnd
};

struct TEvent
{
    EventGroup eventGroup;
    std::uint8_t eventType;
    std::any eventData;
};

enum class TEventKind
{
    EventBegin
};

template <typename TToConvert> constexpr auto to_underlying(TToConvert _valueToConvert)
{
    return static_cast<typename std::underlying_type<TToConvert>::type>(_valueToConvert);
}

enum class TBatteryEvents : std::uint8_t
{
    BatteryEventsStart = to_underlying(TEventKind::EventBegin),
    BatteryLevelChanged,
    BatteryEventsEnd
};

enum class THeartRateEvents : std::uint8_t
{
    HeartRateEventsBegin = to_underlying(TBatteryEvents::BatteryEventsEnd),
    MeasureStarted,
    MeasureCompleted,
    MeasureFailed,
    HeartRateEventsEnd
};

enum class TDateTimeEvents : std::uint8_t
{
    DateTimeEventsBegin = to_underlying(THeartRateEvents::HeartRateEventsEnd),
    DateTimeChanged,
    DateTimeEventsEnd
};

enum class TBleClientEvents : std::uint8_t
{
    BleClientEventsBegin = to_underlying(TDateTimeEvents::DateTimeEventsEnd),
    DeviceConnected,
    DeviceDisconnected,
    BleClientEventsEnd
};

enum class TGraphicsEvents : std::uint8_t
{
    GraphicsEventsBegin = to_underlying(TBleClientEvents::BleClientEventsEnd),
    PageHiding,
    PageActivated,
    GraphicsEventsEnd
};

enum class TButtonsEvents : std::uint8_t
{
    TButtonsEventsBegin = to_underlying(TGraphicsEvents::GraphicsEventsEnd),
    ButtonClicked,
    ButtonPressed,
    ButtonReleased,
    ButtonDblClick,
    ButtonLongClick,
    ButtonEventsEnd
};

enum class HardwareButtonId : std::uint8_t
{
    kLeftButtonTop,
    kLeftButtonMedium,
    kLeftButtonBottom,
    kRightButtonTop,
    kRightButtonBottom
};

} // namespace Graphics::Events
