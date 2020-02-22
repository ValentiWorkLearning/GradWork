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

template< typename ConcretePageView >
class PageViewObject
    :   public ConcretePageView
{

public:

    explicit PageViewObject(
            std::weak_ptr<Theme::IThemeController> _themeController
        ,   std::string_view _pageName
    );

    ~PageViewObject()override = default;

public:

    void addWidget( const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget ) override;

    void show() override;

    void hide() override;

    std::string_view getPageName() const override;

    bool isVisible()const override;

    std::shared_ptr<Theme::IThemeController> getThemeController() override;

private:

    void executeForEachWidget(  std::function<void(std::shared_ptr<Graphics::Widgets::IWidgetObject>&)> _toCall );

    using TWidgetsStorage = std::vector<std::shared_ptr<Graphics::Widgets::IWidgetObject> >;
    TWidgetsStorage m_pWidgetsStorage;

private:

    bool m_isPageVisible;
    std::string_view m_pageName;
    std::weak_ptr<Theme::IThemeController> m_pThemeController;
};

};
