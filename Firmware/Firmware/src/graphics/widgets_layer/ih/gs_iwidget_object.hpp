#pragma once

#include <memory>

namespace Graphics::Views
{
    class IPageViewObject;
};

namespace Graphics::Theme
{
    class IThemeController;
}

namespace Graphics::Widgets
{

class IWidgetObject
{

public:

    virtual ~IWidgetObject() = default;

public:

    virtual void show() = 0;

    virtual void hide() = 0;

    virtual bool isVisible() const = 0;

public:

    virtual const Graphics::Theme::IThemeController* getThemeController() const = 0;
};

};
