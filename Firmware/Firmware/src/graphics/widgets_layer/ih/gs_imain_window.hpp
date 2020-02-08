#pragma once
#include <memory>

namespace Graphics::Views
{
    class IPageViewObject;
}

namespace Graphics::Events
{
    struct TEvent;
    class EventDispatcher;
}

namespace Graphics::MainWindow
{

class IGsMainWindow
{

public:

    virtual ~IGsMainWindow() = default;

    virtual void handleEvent( const Events::TEvent& _tEvent ) = 0;

    virtual void addPage( std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd ) = 0;

    virtual void handleEventTimerEllapsed() = 0;

    virtual Events::EventDispatcher& getEventDispatcher() = 0;
};

};
