#include "gs_page_view_object.hpp"

#include "ih/gs_events.hpp"

#include "widgets/battery/gs_battery_widget.hpp"
#include "widgets/battery/gs_battery_handler.hpp"

#include <algorithm>

#include "pages/clock_page/gs_iclock_page_view.hpp"
#include "pages/health_page/gs_ihealth_page_view.hpp"
#include "pages/player_page/gs_iplayer_page_view.hpp"

#include "gs_itheme_controller.hpp"

namespace Graphics::Views
{

template< typename ConcretePageView >
PageViewObject<ConcretePageView>::PageViewObject(
        const Theme::IThemeController* _themeController
    ,   std::string_view _pageName
    )
    :   m_isPageVisible{ false }
    ,   m_pageName{ _pageName }
    ,   m_pThemeController{ _themeController }
{
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView>::addWidget(
    Graphics::Widgets::IWidgetObject* _pWidget
)
{
    m_pWidgetsStorage.push_back( _pWidget );
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView >::show()
{
    if( m_isPageVisible )
        return;

    initStyles();

    auto parent = lv_disp_get_scr_act( nullptr );

	auto pThemeProvider = PageViewObject::getThemeController();
	if (!pThemeProvider )
		return;

	const std::uint32_t DisplayWidth { pThemeProvider->getDisplayWidth() };
	const std::uint32_t DisplayHeight { pThemeProvider->getDisplayHeight() };

    initPageWidgets( parent, DisplayWidth, DisplayHeight );

    executeForEachWidget(
        []( Graphics::Widgets::IWidgetObject* _pWidget )
        {
                _pWidget->show();
        }
    );
    m_isPageVisible = true;
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView>::hide()
{
    if( !m_isPageVisible )
        return;

    unloadWidgets();
    resetStyle();
    executeForEachWidget(
        []( Graphics::Widgets::IWidgetObject* _pWidget )
        {
                _pWidget->hide();
        }
    );
    m_isPageVisible = false;
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView>::reloadStyle()
{
    resetStyle();
    initStyles();

    executeForEachWidget(
        []( Graphics::Widgets::IWidgetObject* _pWidget )
        {
            _pWidget->reloadStyle();
        }
    );
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
const Theme::IThemeController*
PageViewObject<ConcretePageView>::getThemeController() const
{
    return m_pThemeController;
}

template< typename ConcretePageView >
void PageViewObject<ConcretePageView>::executeForEachWidget(
    std::function<void(Graphics::Widgets::IWidgetObject*)> _toCall
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
template class PageViewObject<typename Views::IPlayerWatchPage>;

};
