#pragma once
#include "lvgl.h"

#include "SimpleSignal.hpp"

namespace Graphics::Theme
{
    enum class ColorTheme
    {
            Night
        ,   Light
        ,   Pastele
    };

    enum class Color
    {
            MainThemeLight
        ,   MainThemeDark
    };

    enum class FontSize
    {
            extra_small //12px
        ,   small   //  16px
        ,   normal  // 20px
        ,   large   //  36px
        ,   x_large //  68px
    };

class IThemeController
{
    public:

    virtual void setActiveTheme( ColorTheme _themeToSet ) = 0;

    virtual lv_style_t getIconsFont( Color _fontColor ) = 0;

    virtual lv_style_t getFontStyle( FontSize _fontStyle, Color _fontColor ) = 0;

    virtual lv_color_t getMainThemeColor(Color _fontColor) = 0;

    virtual std::uint32_t getDisplayWidth() const = 0;

    virtual std::uint32_t getDisplayHeight() const = 0;

    public:

    Simple::Signal<void()> onThemeChanged;

    public:

    virtual ~IThemeController() = default;

};
}