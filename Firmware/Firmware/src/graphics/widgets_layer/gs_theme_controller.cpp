#include "gs_theme_controller.hpp"

namespace
{

    namespace ThemeDark
    {
        static const lv_color_t MainDarkColor = lv_color_make(0x00, 0x33, 0x33);
        static const lv_color_t MainLightColor = lv_color_make(0x99, 0xCC, 0xCC);
    }

    namespace ThemeLight
    {
        static const lv_color_t MainDarkColor = lv_color_make(0x00, 0x00, 0x00);
        static const lv_color_t MainLightColor = lv_color_make(0xFF, 0xFF, 0xFF);
    }

    namespace ThemePastele
    {
        static const lv_color_t MainDarkColor = lv_color_make(0x00, 0x00, 0x00);
        static const lv_color_t MainLightColor = lv_color_make(0xCC, 0xCC, 0xCC);
    }

}

namespace Graphics::Theme
{

lv_color_t
ThemeController::getMainThemeColor( Color _fromColor )
{
    switch (_fromColor)
    {
    case Graphics::Theme::Color::MainThemeLight:
            return m_mainThemeLightColor;
        break;
    case Graphics::Theme::Color::MainThemeDark:
            return m_mainThemeDarkColor;
        break;
    default:
        break;
    }
}

std::uint32_t ThemeController::getDisplayWidth() const
{
    return m_displayWidth;
}

std::uint32_t ThemeController::getDisplayHeight() const
{
    return m_displayHeight;
}

ThemeController::ThemeController(
            const ColorTheme _initialColorTheme
        ,   std::uint32_t _displayWidth
        ,   std::uint32_t _displayHeight
    )
    :   m_activeTheme{ _initialColorTheme }
    ,   m_displayWidth{ _displayWidth }
    ,   m_displayHeight{ _displayHeight }
{
    initColorsAccrodingToTheme( m_activeTheme );
}

void
ThemeController::setActiveTheme( ColorTheme _themeToSet )
{
    if( m_activeTheme != _themeToSet )
    {
        m_activeTheme = _themeToSet;

        initColorsAccrodingToTheme( m_activeTheme );

        onThemeChanged.emit();
    }
};

lv_style_t
ThemeController::getIconsFont( Color _fontColor )
{
    lv_style_t iconsFont{};
    lv_style_copy( &iconsFont,&lv_style_plain_color );

    iconsFont.text.font = &IconFont16px;
    iconsFont.text.color = getMainThemeColor( _fontColor );

    return  iconsFont;
};

lv_style_t
ThemeController::getFontStyle( FontSize _fontStyle, Color _fontColor )
{
    lv_style_t fontStyle{};
    lv_style_copy( &fontStyle, &lv_style_plain_color );

    switch (_fontStyle)
    {
    case Graphics::Theme::FontSize::small:
        fontStyle.text.font = &LcdNova16px;
        break;
    case Graphics::Theme::FontSize::medium:
        fontStyle.text.font = &LcdNova36px;
        break;
    case Graphics::Theme::FontSize::large:
        fontStyle.text.font = &LcdNova40px;
        break;
    case Graphics::Theme::FontSize::x_large:
        fontStyle.text.font = &LcdNova68px;
        break;
    default:
        break;
    }

    fontStyle.text.color = getMainThemeColor( _fontColor );

    return fontStyle;
}


void ThemeController::initColorsAccrodingToTheme(ColorTheme _theme)
{
    switch (_theme)
    {
    case Graphics::Theme::ColorTheme::Night:
        m_mainThemeDarkColor = ThemeDark::MainDarkColor;
        m_mainThemeLightColor = ThemeDark::MainLightColor;
        break;
    case Graphics::Theme::ColorTheme::Light:
        m_mainThemeDarkColor = ThemeLight::MainDarkColor;
        m_mainThemeLightColor = ThemeLight::MainLightColor;
        break;
    case Graphics::Theme::ColorTheme::Pastele:
        m_mainThemeDarkColor = ThemePastele::MainDarkColor;
        m_mainThemeLightColor = ThemePastele::MainLightColor;
        break;
    default:
        break;
    }
}


std::shared_ptr<IThemeController>
createThemeController(
        const ColorTheme _initialColorTheme
    ,   std::uint32_t _displayWidth
    ,   std::uint32_t _displayHeight
)
{
    return std::make_shared<ThemeController>(
            _initialColorTheme
        ,   _displayWidth
        ,   _displayHeight
    );
}

}