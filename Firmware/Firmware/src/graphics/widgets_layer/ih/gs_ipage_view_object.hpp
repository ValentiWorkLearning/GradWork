#pragma once

#include <memory>

namespace Graphics::Widgets
{
    class IWidgetObject;
}

namespace EventDispatcher::Events
{
    struct Event;
}

namespace Graphics::Views
{

class IPageViewObject
{

public:

    virtual ~IPageViewObject() = default;

public:

    virtual void addWidget( const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget ) = 0;

    virtual void handleEvent( const EventDispatcher::Events::Event& _tEvent ) = 0;

    virtual void show() = 0;

    virtual void hide() = 0;
};

};
