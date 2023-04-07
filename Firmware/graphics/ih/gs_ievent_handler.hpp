#pragma once
#include "gs_events.hpp"

#include <memory>

namespace Graphics::Events
{
struct TEvent;
class EventDispatcher;
} // namespace Graphics::Events

namespace Graphics
{
class IEventHandler
{

public:
    virtual ~IEventHandler() = default;

public:
    virtual void handleEvent(const Events::TEvent& _event) noexcept = 0;

public:
    virtual void initSubscriptions(Events::EventDispatcher& eventDispatcher) = 0;
    virtual void deinitHandler() = 0;
};

using TEventHandlerPtr = std::unique_ptr<Graphics::IEventHandler>;
} // namespace Graphics