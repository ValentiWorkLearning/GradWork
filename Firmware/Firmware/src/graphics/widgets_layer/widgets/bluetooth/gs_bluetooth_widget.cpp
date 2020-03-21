#include "gs_bluetooth_widget.hpp"
#include "gs_events.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "IconFont16px.hpp"

namespace Graphics::Widgets
{

BluetoothWidget::BluetoothWidget( const Theme::IThemeController* _themeController )
    :   WidgetBaseObj<IBluetoothWidget>{ _themeController }
{
    initStyles();
}

void BluetoothWidget::show()
{
    WidgetBaseObj::show();

    const auto[parent, DisplayWidth, DisplayHeight ] = WidgetBaseObj::getShowParams();

    initBluetoothIcon( parent, DisplayWidth, DisplayHeight );

}

void BluetoothWidget::initStyles()
{
    auto pThemeProvider = WidgetBaseObj::getThemeController();
    if (!pThemeProvider )
        return;

    m_bluetoothIconStyle = pThemeProvider->getIconsFont(
            Theme::FontSize::small
        ,   Theme::Color::MainThemeDark
    );

}

void BluetoothWidget::initBluetoothIcon(
        lv_obj_t* _parentObject
    ,   const std::uint32_t _displayWidth
    ,   const std::uint32_t _displayHeight
)
{

    m_pBluetoothIcon.reset( lv_label_create( _parentObject, nullptr) );

    const std::uint32_t DisplayWidth{ _displayWidth };
    const std::uint32_t DisplayHeight{ _displayHeight };

    lv_obj_set_style( m_pBluetoothIcon.get(), &m_bluetoothIconStyle );
    lv_label_set_text( m_pBluetoothIcon.get(), IconFontSymbols::Bluetooth::BluetoothEnabled.data() );

    lv_obj_align(
            m_pBluetoothIcon.get()
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_LEFT
        ,   static_cast<int>( DisplayWidth / 6)
        ,   static_cast<int>( DisplayHeight / 3.5f)
    );
}


void BluetoothWidget::hide()
{
    WidgetBaseObj::hide();

    Meta::tupleApply(
            []( auto&& _nodeToReset ){ _nodeToReset.reset(); }
        ,   std::forward_as_tuple(
                m_pBluetoothIcon
        )
    );
}

void BluetoothWidget::setBluetoothStatus(BluetoothStatus _iconToSet)
{
}

std::unique_ptr<IBluetoothWidget> createBluetoothWidget(
    const Theme::IThemeController* _themeController
)
{
    return std::make_unique<BluetoothWidget>( _themeController );
}


};
