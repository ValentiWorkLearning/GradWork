#pragma once
#include <memory>

namespace Graphics::Views
{
    class IPageViewObject;
}

namespace EventDispatcher::Events
{
    struct Event{};
}

namespace Graphics::MainWindow
{

class IGsMainWindow
{

public:

    virtual ~IGsMainWindow() = default;

    virtual void handleEvent( const EventDispatcher::Events::Event& _tEvent ) = 0;

    virtual void addPage( std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd ) = 0;

    virtual void handleEventTimerEllapsed() = 0;
};

};