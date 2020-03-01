#pragma once
#include <memory>
#include <string>

#include "SimpleSignal.hpp"

namespace Graphics::Views
{
    class IPageViewObject;
}

namespace Graphics::Events
{
    struct TEvent;
    class EventDispatcher;
}

namespace Graphics::Theme
{
    class IThemeController;
}

namespace Graphics::MainWindow
{

class IGsMainWindow
{

public:

    virtual ~IGsMainWindow() = default;

public:

    virtual void handleEvent( const Events::TEvent& _tEvent ) = 0;

    virtual void addPage(
        std::shared_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    ) = 0;

    virtual void setPageActive( std::string_view _pageName ) = 0;

    virtual std::shared_ptr<Graphics::Views::IPageViewObject>
        getPage(std::string_view _pageName) = 0;

    virtual void handleEventTimerEllapsed() = 0;

    virtual Events::EventDispatcher& getEventDispatcher() = 0;

    virtual std::weak_ptr<Theme::IThemeController> getThemeController() const = 0;

public:

    Simple::Signal<void(std::string_view)> onActivePageChanged;

};

};
