#include "gs_bluetooth_widget.hpp"
#include "ih/gs_events.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "fonts/IconFont16px.hpp"

namespace Graphics::Widgets
{

BluetoothWidget::BluetoothWidget( const Theme::IThemeController* _themeController )
    :   WidgetBaseObj<IBluetoothWidget>{ _themeController }
    ,   m_currentStatus{ BluetoothStatus::Disconnected }
    ,   m_bluetoothIconStyle{}
{
    initStyles();
}

void BluetoothWidget::show()
{
    auto CurrentStatus = getCurrentStatus();

    if( CurrentStatus != BluetoothStatus::Disconnected )
    {
        WidgetBaseObj::show();
    
        const auto[ parent, DisplayWidth, DisplayHeight ] = WidgetBaseObj::getShowParams();
    
        initBluetoothIcon( parent, DisplayWidth, DisplayHeight );
    }
}

void BluetoothWidget::reloadStyle()
{
    resetStyle();
    initStyles();
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

void BluetoothWidget::resetStyle()
{
	Meta::tupleApply(
		[](auto&& _nodeToReset) { 	lv_style_reset( &_nodeToReset ); }
		,   std::forward_as_tuple(
            m_bluetoothIconStyle
		)
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

    lv_obj_add_style( m_pBluetoothIcon.get(), LV_PART_MAIN,LV_STATE_DEFAULT,&m_bluetoothIconStyle );
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
    m_currentStatus = _iconToSet;

    if( _iconToSet == BluetoothStatus::Connected )
        show();
    else
        hide();
}

IBluetoothWidget::BluetoothStatus
BluetoothWidget::getCurrentStatus() const
{
    return m_currentStatus;
}

std::unique_ptr<IBluetoothWidget> createBluetoothWidget(
    const Theme::IThemeController* _themeController
)
{
    return std::make_unique<BluetoothWidget>( _themeController );
}


};
