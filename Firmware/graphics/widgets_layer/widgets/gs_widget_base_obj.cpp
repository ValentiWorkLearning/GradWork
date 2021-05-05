#include "gs_widget_base_obj.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_itheme_controller.hpp"

#include "ih/widgets/gs_ibattery_widget.hpp"
#include "ih/widgets/gs_ipages_switch.hpp"
#include "ih/widgets/gs_ibluetooth_widget.hpp"

namespace Graphics::Widgets
{

template< typename TBaseWidgetInterface >
WidgetBaseObj<TBaseWidgetInterface>::WidgetBaseObj(
        const Theme::IThemeController* _themeController
    )noexcept
    :   m_isWidgetVisible{ false }
    ,   m_pThemeController{ _themeController }
{
}

template< typename TBaseWidgetInterface >
void
WidgetBaseObj<TBaseWidgetInterface>::show() noexcept
{
    m_isWidgetVisible = true;
}


template< typename TBaseWidgetInterface >
void
WidgetBaseObj<TBaseWidgetInterface>::hide()noexcept
{
    m_isWidgetVisible = false;
}

template< typename TBaseWidgetInterface >
bool
WidgetBaseObj<TBaseWidgetInterface>::isVisible()const noexcept
{
    return m_isWidgetVisible;
}

template< typename TBaseWidgetInterface >
typename WidgetBaseObj<TBaseWidgetInterface>::ShowParams
WidgetBaseObj<TBaseWidgetInterface>::getShowParams()noexcept
{
    auto pThemeProvider = getThemeController();
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
const Theme::IThemeController*
WidgetBaseObj<TBaseWidgetInterface>::getThemeController() const noexcept
{
    return m_pThemeController;
}
;


template class WidgetBaseObj<typename Widgets::IBatteryWidget>;
template class WidgetBaseObj<typename Widgets::IPagesSwitch>;
template class WidgetBaseObj<typename Widgets::IBluetoothWidget>;

};
