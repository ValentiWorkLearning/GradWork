#pragma once
#include "gs_events.hpp"

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
}