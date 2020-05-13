#include "gs_battery_widget.hpp"
#include "gs_events.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "IconFont16px.hpp"
#include <charconv>

namespace Graphics::Widgets
{

BatteryWidget::BatteryWidget( const Theme::IThemeController* _themeController )
    :   WidgetBaseObj<IBatteryWidget>{ _themeController }
    ,   m_labelText{ "90%" }
    ,   m_currentStatus{ Graphics::Widgets::IBatteryWidget::BatteryStatus::Charged90Percents }
{
    initStyles();
}

void BatteryWidget::show()
{
    WidgetBaseObj::show();

    const auto[parent, DisplayWidth, DisplayHeight ] = WidgetBaseObj::getShowParams();

    initBatteryIcon( parent, DisplayWidth, DisplayHeight );
    initBatteryPercentageLabel( parent, DisplayWidth, DisplayHeight );

}

void BatteryWidget::reloadStyle()
{
    resetStyle();
    initStyles();
}

void BatteryWidget::initStyles()
{
    auto pThemeProvider = WidgetBaseObj::getThemeController();
    if (!pThemeProvider )
        return;

    m_batteryLabelStyle = pThemeProvider->getFontStyle(
            Theme::FontSize::small
        ,   Theme::Color::MainThemeLight
    );

    m_bateryIconStyle = pThemeProvider->getIconsFont(
            Theme::FontSize::small
        ,   Theme::Color::MainThemeLight
    );

}

void BatteryWidget::resetStyle()
{
    Meta::tupleApply(
		[](auto&& _nodeToReset) { 	lv_style_reset( &_nodeToReset ); }
		,   std::forward_as_tuple(
                m_batteryLabelStyle
            ,   m_bateryIconStyle
		)
	);
}

void BatteryWidget::setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel )
{
    if( _newBatteryLevel == 100 )
        m_labelText = "  ";

    constexpr std::uint8_t arraySize = 4;
    std::array<char, arraySize> tempStr{};

    auto [p, ec] = std::to_chars(
            tempStr.data()
        ,   tempStr.data() + tempStr.size()
        ,   _newBatteryLevel
    );

    m_labelText = std::string_view( tempStr.data(), p - tempStr.data() );
    m_labelText += '%';
    lv_label_set_text( m_pBatteryLabel.get(), m_labelText.c_str() );
}

void BatteryWidget::setBatteryStatus( BatteryStatus _iconToSet )
{
    switch (_iconToSet)
    {
    case Graphics::Widgets::IBatteryWidget::BatteryStatus::QuaterCharge:
        lv_label_set_text( m_pBatteryIcon.get(), IconFontSymbols::Battery::Battery25Percent.data() );
        break;
    case Graphics::Widgets::IBatteryWidget::BatteryStatus::HalfCharged:
        lv_label_set_text( m_pBatteryIcon.get(), IconFontSymbols::Battery::Battery50Percent.data() );
        break;
    case Graphics::Widgets::IBatteryWidget::BatteryStatus::Charge75Percents:
        lv_label_set_text( m_pBatteryIcon.get(), IconFontSymbols::Battery::Battery75Percent.data() );
        break;
    case Graphics::Widgets::IBatteryWidget::BatteryStatus::Charged90Percents:
        lv_label_set_text( m_pBatteryIcon.get(), IconFontSymbols::Battery::Battery90Percent.data() );
        break;
    case Graphics::Widgets::IBatteryWidget::BatteryStatus::FullCharged:
        lv_label_set_text( m_pBatteryIcon.get(), IconFontSymbols::Battery::BatteryCharged.data() );
        break;
    default:
        break;
    }

    m_currentStatus = _iconToSet;
}

void BatteryWidget::initBatteryPercentageLabel(
        lv_obj_t* _parentObject
    ,   const std::uint32_t _displayWidth
    ,   const std::uint32_t _displayHeight
)
{

    m_pBatteryLabel.reset( lv_label_create( _parentObject, nullptr) );

    lv_obj_add_style( m_pBatteryLabel.get(), LV_OBJ_PART_MAIN,&m_batteryLabelStyle );

    const std::uint32_t DisplayWidth { _displayWidth };
    const std::uint32_t DisplayHeight { _displayHeight };

    lv_label_set_text(m_pBatteryLabel.get(), m_labelText.data() );

    lv_obj_align(
            m_pBatteryLabel.get()
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_RIGHT
        ,   -static_cast<int>( DisplayWidth / 4)
        ,   static_cast<int>( DisplayHeight / 4) + static_cast<int>( DisplayHeight / 20)
    );
}

void BatteryWidget::initBatteryIcon(
        lv_obj_t* _parentObject
    ,   const std::uint32_t _displayWidth
    ,   const std::uint32_t _displayHeight
)
{

    m_pBatteryIcon.reset( lv_label_create( _parentObject, nullptr) );

    const std::uint32_t DisplayWidth{ _displayWidth };
    const std::uint32_t DisplayHeight{ _displayHeight };

    lv_obj_add_style( m_pBatteryIcon.get(), LV_OBJ_PART_MAIN,&m_bateryIconStyle );
    setBatteryStatus( m_currentStatus );

    lv_obj_align(
            m_pBatteryIcon.get()
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_RIGHT
        ,   -static_cast<int>( DisplayWidth / 7 )
        ,   static_cast<int>( DisplayHeight / 4 ) + static_cast<int>( DisplayHeight / 22)
    );
}


void BatteryWidget::hide()
{
    WidgetBaseObj::hide();

    Meta::tupleApply(
            []( auto&& _nodeToReset ){ _nodeToReset.reset(); }
        ,   std::forward_as_tuple(
                m_pBatteryIcon
            ,   m_pBatteryLabel
        )
    );
}

std::unique_ptr<IBatteryWidget> createBatteryWidget(
    const Theme::IThemeController* _themeController
)
{
    return std::make_unique<BatteryWidget>( _themeController );
}


};
