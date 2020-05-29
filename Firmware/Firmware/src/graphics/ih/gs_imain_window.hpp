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

class IGsMainWindowModel
{

public:

    virtual ~IGsMainWindowModel() = default;

public:

    virtual void handleEvent( const Events::TEvent& _tEvent ) = 0;

    virtual void addPage(
        std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    ) = 0;

    virtual void setPageActive( std::string_view _pageName ) = 0;

    virtual Graphics::Views::IPageViewObject& getActivePage() = 0;

    virtual const Graphics::Views::IPageViewObject& getActivePage() const = 0;

    virtual const Graphics::Views::IPageViewObject&
        getPage(std::string_view _pageName)const = 0;

    using TPageWalker = std::function<void(Graphics::Views::IPageViewObject&)>;

    virtual void forEachPage(TPageWalker _pageWalker) = 0;

public:

    virtual void handleEventTimerEllapsed() = 0;

    virtual Events::EventDispatcher& getEventDispatcher() = 0;

    virtual const Theme::IThemeController* getThemeController() const = 0;

    virtual Theme::IThemeController* getThemeController() = 0;

public:

    Simple::Signal<void(std::string_view)> onActivePageChanged;

};


class IMainWindowView
{

public:

    virtual ~IMainWindowView() = default;

public:

    virtual void initBackground() = 0;

    virtual void resetBackgroundStyle() = 0;

public:

    virtual const Theme::IThemeController* getThemeController() const = 0;

    virtual Theme::IThemeController* getThemeController() = 0;
};

};
