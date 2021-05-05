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
    )noexcept;

    void setActiveTheme( ColorTheme _themeToSet )noexcept override;

    ColorTheme getActiveTheme()const noexcept override;

public:

    lv_style_t getIconsFont( FontSize _fontStyle, Color _fontColor )const noexcept override;

    lv_style_t getFontStyle( FontSize _fontStyle, Color _fontColor )const noexcept override;

    lv_color_t getMainThemeColor( Color _fontColor )const noexcept override;

    std::uint32_t getDisplayWidth() const noexcept override;

    std::uint32_t getDisplayHeight() const noexcept override;

public:

    ~ThemeController()override = default;

private:

    void initColorsAccrodingToTheme( ColorTheme _theme )noexcept;

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
)noexcept;

}