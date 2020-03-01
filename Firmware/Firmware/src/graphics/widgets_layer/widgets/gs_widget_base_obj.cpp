#include "gs_widget_base_obj.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_itheme_controller.hpp"

#include "battery/gs_ibattery_widget.hpp"
#include "pages_switch/gs_ipages_switch.hpp"


namespace Graphics::Widgets
{

template< typename TBaseWidgetInterface >
WidgetBaseObj<TBaseWidgetInterface>::WidgetBaseObj(
        std::weak_ptr<Theme::IThemeController> _themeController
    )
    :   m_isWidgetVisible{ false }
    ,   m_pThemeController{ _themeController }
{
}

template< typename TBaseWidgetInterface >
void
WidgetBaseObj<TBaseWidgetInterface>::show()
{
    m_isWidgetVisible = true;
}


template< typename TBaseWidgetInterface >
void
WidgetBaseObj<TBaseWidgetInterface>::hide()
{
    m_isWidgetVisible = false;
}

template< typename TBaseWidgetInterface >
bool
WidgetBaseObj<TBaseWidgetInterface>::isVisible()const
{
    return m_isWidgetVisible;
}

template< typename TBaseWidgetInterface >
typename WidgetBaseObj<TBaseWidgetInterface>::ShowParams
WidgetBaseObj<TBaseWidgetInterface>::getShowParams()
{
    auto pThemeProvider = getThemeController().lock();
    if (!pThemeProvider)
        return {};

    auto parent = lv_disp_get_scr_act(nullptr);

    return WidgetBaseObj<TBaseWidgetInterface>::ShowParams{
            parent
        ,   pThemeProvider->getDisplayWidth()
        ,   pThemeProvider->getDisplayHeight()
    };
}

template<typename TBaseWidgetInterface>
std::weak_ptr<Theme::IThemeController>
WidgetBaseObj<TBaseWidgetInterface>::getThemeController() const
{
    return m_pThemeController;
}
;


template class WidgetBaseObj<typename Widgets::IBatteryWidget>;
template class WidgetBaseObj<typename Widgets::IPagesSwitch>;

};
