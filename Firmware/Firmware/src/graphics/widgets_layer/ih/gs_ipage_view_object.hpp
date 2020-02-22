#pragma once

#include <memory>
#include <string>

namespace Graphics::Widgets
{
    class IWidgetObject;
}

namespace Graphics::Theme
{
    class IThemeController;
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

    virtual void show() = 0;

    virtual void hide() = 0;

    virtual bool isVisible() const = 0;

    virtual std::string_view getPageName() const = 0;

    virtual std::shared_ptr<Theme::IThemeController> getThemeController() = 0;
};

};
