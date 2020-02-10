#include "ih/gs_itheme_controller.hpp"

#include <memory>

namespace Graphics::Theme
{

class ThemeController
    :   public IThemeController
{

public:

    explicit ThemeController( const ColorTheme _initialColorTheme );

    void setActiveTheme( ColorTheme _themeToSet ) override;

    lv_style_t getIconsFont( Color _fontColor ) override;

    lv_style_t getFontStyle( FontSize _fontStyle, Color _fontColor ) override;

    lv_color_t getMainThemeColor( Color _fontColor ) override;

public:

    ~ThemeController()override = default;

private:

    void initColorsAccrodingToTheme( ColorTheme _theme );

private:

    ColorTheme m_activeTheme;

    lv_color_t m_mainThemeDarkColor;
    lv_color_t m_mainThemeLightColor;

};

std::shared_ptr<IThemeController> createThemeController( const ColorTheme _initialColorTheme );

}