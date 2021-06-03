#pragma once

#include "ih/gs_events.hpp"

#include "utils/Noncopyable.hpp"

#include <any>
#include <atomic>
#include <functional>
#include <memory>
#include <vector>

#include <etl/queue_spsc_atomic.h>
#include <etl/vector.h>

namespace Graphics::Events
{

class EventDispatcher : private Utils::noncopyable
{

public:
    using TEventHandler = std::function<void(const TEvent&)>;

    static constexpr inline int MaxSubscriberLimit = 3;
    using SubscriberStorage = etl::vector<TEventHandler, MaxSubscriberLimit>;

    void subscribe(EventGroup _eventGroup, const TEventHandler& _handler) noexcept;

    void postEvent(TEvent&& _eventToProcess) noexcept;

    void processEventQueue() noexcept;

private:
    static constexpr inline int EventsCount =
        Events::enumConvert<EventGroup>(EventGroup::EventGroupEnd);
    static constexpr inline int EventPoolSize = 16;

    using TEventsMap = etl::vector<std::pair<EventGroup, SubscriberStorage>, EventsCount>;
    TEventsMap m_eventsMap;

    using TEventsQueue =
        etl::queue_spsc_atomic<TEvent, EventPoolSize, etl::memory_model::MEMORY_MODEL_SMALL>;
    TEventsQueue m_eventsQueue;
};

using TEventDispatcherPtr = std::unique_ptr<EventDispatcher>;

TEventDispatcherPtr createEventDispatcher() noexcept;

} // namespace Graphics::Events
