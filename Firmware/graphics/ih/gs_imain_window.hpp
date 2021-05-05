#pragma once
#include <memory>
#include <string>

#include "utils/SimpleSignal.hpp"

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

    virtual void handleEvent( const Events::TEvent& _tEvent )noexcept = 0;

    virtual void addPage(
        std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    )noexcept = 0;

    virtual void setPageActive( std::string_view _pageName )noexcept = 0;

    virtual Graphics::Views::IPageViewObject& getActivePage()noexcept = 0;

    virtual const Graphics::Views::IPageViewObject& getActivePage() const noexcept = 0;

    virtual const Graphics::Views::IPageViewObject&
        getPage(std::string_view _pageName)const noexcept = 0;

    using TPageWalker = std::function<void(Graphics::Views::IPageViewObject&)>;

    virtual void forEachPage(TPageWalker _pageWalker) noexcept = 0;

public:

    virtual void handleEventTimerEllapsed()noexcept = 0;

    virtual Events::EventDispatcher& getEventDispatcher()noexcept = 0;

    virtual const Theme::IThemeController* getThemeController() const noexcept = 0;

    virtual Theme::IThemeController* getThemeController() noexcept = 0;

public:

    Simple::Signal<void(std::string_view)> onActivePageChanged;

};


class IMainWindowView
{

public:

    virtual ~IMainWindowView() = default;

public:

    virtual void initBackground()noexcept = 0;

    virtual void resetBackgroundStyle()noexcept = 0;

public:

    virtual const Theme::IThemeController* getThemeController() const noexcept = 0;

    virtual Theme::IThemeController* getThemeController() noexcept = 0;
};

};
