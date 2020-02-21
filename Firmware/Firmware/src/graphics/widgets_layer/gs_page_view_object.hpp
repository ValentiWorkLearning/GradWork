#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <vector>
#include <functional>

namespace Graphics::Events
{
    struct TEvent;
}

namespace Graphics::Views
{

class PageViewObject
    :   public IPageViewObject
{

public:

    PageViewObject( std::weak_ptr<Theme::IThemeController> _themeController );

    ~PageViewObject()override = default;

public:

    void addWidget( const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget ) override;

    void show() override;

    void hide() override;

    bool isVisible()const override;

    std::shared_ptr<Theme::IThemeController> getThemeController() override;

private:

    void executeForEachWidget(  std::function<void(std::shared_ptr<Graphics::Widgets::IWidgetObject>&)> _toCall );

    using TWidgetsStorage = std::vector<std::shared_ptr<Graphics::Widgets::IWidgetObject> >;
    TWidgetsStorage m_pWidgetsStorage;

private:

    bool m_isPageVisible;
    std::weak_ptr<Theme::IThemeController> m_pThemeController;
};

};
