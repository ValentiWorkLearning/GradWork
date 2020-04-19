#include "ih/gs_itheme_controller.hpp"

#include <memory>

namespace Graphics::Theme
{

class ThemeController
    :   public IThemeController
{

public:

    explicit ThemeController(
            const ColorTheme _initialColorTheme
        ,   std::uint32_t _displayWidth
        ,   std::uint32_t _displayHeight
    );

    void setActiveTheme( ColorTheme _themeToSet ) override;

    ColorTheme getActiveTheme()const override;

public:

    lv_style_t getIconsFont( FontSize _fontStyle, Color _fontColor )const override;

    lv_style_t getFontStyle( FontSize _fontStyle, Color _fontColor )const override;

    lv_color_t getMainThemeColor( Color _fontColor )const override;

    std::uint32_t getDisplayWidth() const override;

    std::uint32_t getDisplayHeight() const override;

public:

    ~ThemeController()override = default;

private:

    void initColorsAccrodingToTheme( ColorTheme _theme );

private:

    ColorTheme m_activeTheme;

    const std::uint32_t m_displayWidth;
    const std::uint32_t m_displayHeight;

    lv_color_t m_mainThemeDarkColor;
    lv_color_t m_mainThemeLightColor;

};

std::unique_ptr<IThemeController> createThemeController(
        const ColorTheme _initialColorTheme
    ,   std::uint32_t _displayWidth
    ,   std::uint32_t _displayHeight
);

}