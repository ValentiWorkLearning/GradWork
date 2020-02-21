#include "gs_battery_widget.hpp"
#include "gs_events.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "IconFont16px.hpp"

namespace Graphics::Widgets
{

BatteryWidget::BatteryWidget( std::weak_ptr<Theme::IThemeController> _themeController )
    :   m_pThemeController{ _themeController }
    ,   m_isVisible{ false }
{
    initStyles();
}

void BatteryWidget::show()
{
    auto parent = lv_disp_get_scr_act( nullptr );

    auto pThemeProvider = m_pThemeController.lock();
    if (!pThemeProvider)
        return;

    const std::uint32_t DisplayWidth { pThemeProvider->getDisplayWidth() };
    const std::uint32_t DisplayHeight { pThemeProvider->getDisplayHeight() };

    initBatteryIcon( parent, DisplayWidth, DisplayHeight );
    initBatteryPercentageLabel( parent, DisplayWidth, DisplayHeight );

    m_isVisible = true;
}

void BatteryWidget::initStyles()
{
    auto pThemeProvider = m_pThemeController.lock();
    if (!pThemeProvider )
        return;

    m_batteryLabelStyle = pThemeProvider->getFontStyle(
            Theme::FontSize::small
        ,   Theme::Color::MainThemeLight
    );

    m_bateryIconStyle = pThemeProvider->getIconsFont(
        Theme::Color::MainThemeLight
    );

}

void BatteryWidget::setBatteryLevelPercentage( const std::uint8_t _newBatteryLevel )
{
    if( _newBatteryLevel == 100 )
        m_labelText = "  ";

    m_labelText = std::to_string(_newBatteryLevel) + '%';
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
}

void BatteryWidget::initBatteryPercentageLabel(
        lv_obj_t* _parentObject
    ,   const std::uint32_t _displayWidth
    ,   const std::uint32_t _displayHeight
)
{

    m_pBatteryLabel.reset( lv_label_create( _parentObject, nullptr) );

    lv_obj_set_style( m_pBatteryLabel.get(), &m_batteryLabelStyle );

    const std::uint32_t DisplayWidth { _displayWidth };
    const std::uint32_t DisplayHeight { _displayHeight };

    lv_label_set_text(m_pBatteryLabel.get(), "92%");

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

    lv_obj_set_style( m_pBatteryIcon.get(), &m_bateryIconStyle );
    lv_label_set_text( m_pBatteryIcon.get(), IconFontSymbols::Battery::BatteryCharged.data());

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
    m_pBatteryIcon.reset();
    m_pBatteryLabel.reset();

    m_isVisible = false;
}

bool BatteryWidget::isVisible() const
{
    return m_isVisible;
}

std::shared_ptr<IBatteryWidget> createBatteryWidget(
    std::weak_ptr<Theme::IThemeController> _themeController
)
{
    return std::make_shared<BatteryWidget>( _themeController );
}


};
