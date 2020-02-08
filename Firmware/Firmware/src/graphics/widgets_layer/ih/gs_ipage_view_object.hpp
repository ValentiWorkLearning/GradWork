#pragma once

#include <memory>

namespace Graphics::Widgets
{
    class IWidgetObject;
}

namespace Graphics::Views
{

class IEventHandler;

class IPageViewObject
{

public:

    virtual ~IPageViewObject() = default;

public:

    virtual void addWidget( const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget ) = 0;

    virtual IEventHandler& getEventHandler() = 0;

    virtual IEventHandler& getEventHandler() const = 0;

    virtual void show() = 0;

    virtual void hide() = 0;
};

};
