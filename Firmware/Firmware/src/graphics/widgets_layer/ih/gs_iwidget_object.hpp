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

    virtual void show() = 0;

    virtual void hide() = 0;

    virtual bool isVisible() const = 0;
};

};
