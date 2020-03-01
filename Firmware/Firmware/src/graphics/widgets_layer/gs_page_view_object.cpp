#include "gs_page_view_object.hpp"

#include "ih/gs_events.hpp"

#include "widgets/battery/gs_battery_widget.hpp"
#include "widgets/battery/gs_battery_handler.hpp"

#include <algorithm>

#include "pages/clock_page/gs_iclock_page_view.hpp"
#include "pages/health_page/gs_ihealth_page_view.hpp"

namespace Graphics::Views
{

template< typename ConcretePageView >
PageViewObject<ConcretePageView>::PageViewObject(
        std::weak_ptr<Theme::IThemeController> _themeController
    ,   std::string_view _pageName
    )
    :   m_isPageVisible{ false }
    ,   m_pageName{ _pageName }
    ,   m_pThemeController{ _themeController }
{
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView>::addWidget(
    const std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget
)
{
    m_pWidgetsStorage.push_back( _pWidget );
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView >::show()
{
    executeForEachWidget(
        []( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
        {
                _pWidget->show();
        }
    );
    m_isPageVisible = true;
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView>::hide()
{
    executeForEachWidget(
        []( std::shared_ptr<Graphics::Widgets::IWidgetObject>& _pWidget )
        {
                _pWidget->hide();
        }
    );
    m_isPageVisible = false;
}

template<typename ConcretePageView>
std::string_view PageViewObject<ConcretePageView>::getPageName() const
{
    return m_pageName;
}

template< typename ConcretePageView >
bool PageViewObject<ConcretePageView>::isVisible() const
{
    return m_isPageVisible;
}

template< typename ConcretePageView >
std::shared_ptr<Theme::IThemeController>
PageViewObject<ConcretePageView>::getThemeController()
{
    return m_pThemeController.lock();
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView>::executeForEachWidget(
    std::function<void(std::shared_ptr<Graphics::Widgets::IWidgetObject>&)> _toCall
)
{
    std::for_each(
            m_pWidgetsStorage.begin()
        ,   m_pWidgetsStorage.end()
        ,   _toCall
    );
}

template class PageViewObject<typename Views::IClockWatchPage>;
template class PageViewObject<typename Views::IHealthWatchPage>;

};
