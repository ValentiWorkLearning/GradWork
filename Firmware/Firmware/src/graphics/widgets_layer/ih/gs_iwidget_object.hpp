#pragma once

namespace EventDispatcher::Events
{
    struct Event;
};

namespace Graphics::Views
{
    class IPageViewObject;
};

namespace Graphics::Widgets
{
class IWidgetObject
{

public:

    virtual ~IWidgetObject() = default;

public:

    virtual void handleEvent( const EventDispatcher::Events::Event& _tEvent ) = 0;

    virtual void show() = 0;

    virtual void hide() = 0;
};

};
