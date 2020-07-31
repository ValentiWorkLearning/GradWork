#pragma once
#include "gs_events.hpp"

#include <memory>

namespace Graphics::Events
{
    struct TEvent;
}

namespace Graphics
{
    class IEventHandler
    {

    public:
        virtual ~IEventHandler() = default;

    public:
         virtual void handleEvent( const Events::TEvent& _event ) = 0;
    };

    using TEventHandlerPtr = std::unique_ptr<Graphics::IEventHandler>;
}