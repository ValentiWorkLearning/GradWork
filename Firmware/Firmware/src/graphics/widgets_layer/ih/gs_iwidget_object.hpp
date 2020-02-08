#pragma once

namespace Graphics::Views
{
    class IPageViewObject;
};

namespace Graphics::Widgets
{

class IEventHandler;

class IWidgetObject
{

public:

    virtual ~IWidgetObject() = default;

public:

    virtual IEventHandler& getEventHandler() = 0;

    virtual IEventHandler& getEventHandler() const = 0;

    virtual void show() = 0;

    virtual void hide() = 0;
};

};
