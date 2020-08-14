#pragma once
 
#include <gmock/gmock.h>

#include "ih/gs_imain_window.hpp"
#include "ih/gs_itheme_controller.hpp"

#include <string>


namespace Graphics::Theme
{

class StubThemeController
    :   public IThemeController
{

    void setActiveTheme(ColorTheme _themeToSet) override
    {
    }

    ColorTheme getActiveTheme()const override
    {
        return Graphics::Theme::ColorTheme::Pastele;
    }

public:

    lv_style_t getIconsFont(FontSize _fontStyle, Color _fontColor)const override
    {
        lv_style_t stubFont{};
        lv_style_set_text_font(&stubFont, LV_STATE_DEFAULT, &IconFont16px);
        lv_style_set_text_color(&stubFont, LV_STATE_DEFAULT, getMainThemeColor(_fontColor));
        return stubFont;
    }

    lv_style_t getFontStyle(FontSize _fontStyle, Color _fontColor)const override
    {
        lv_style_t stubFont{};
        lv_style_set_text_font(&stubFont, LV_STATE_DEFAULT, &IconFont16px);
        lv_style_set_text_color(&stubFont, LV_STATE_DEFAULT, getMainThemeColor(_fontColor));
        return stubFont;
    }

    lv_color_t getMainThemeColor(Color _fontColor)const override
    {
        return lv_color_make(0xFF, 0xFF, 0xFF);
    }

    std::uint32_t getDisplayWidth() const override
    {
        return 240;
    }

    std::uint32_t getDisplayHeight() const override
    {
        return 240;
    }

public:

    ~StubThemeController()override = default;

};

std::unique_ptr<IThemeController> createStubThemeController()
{
    return std::make_unique<StubThemeController>();
}

}

namespace Graphics::StubMainWindow
{

class StubMainWindowView
    :   public Graphics::MainWindow::IMainWindowView
{

public:

    StubMainWindowView()
        :   m_pThemeController{
            Graphics::Theme::createStubThemeController()
        }
    {
    }

    virtual ~StubMainWindowView() = default;

public:

    void initBackground()override
    {
    }

    void resetBackgroundStyle()override
    {
    }

public:

    const Theme::IThemeController* getThemeController() const override
    {
        return m_pThemeController.get();
    }

    Theme::IThemeController* getThemeController() override
    {
        return m_pThemeController.get();
    }

private:

    std::unique_ptr<Theme::IThemeController> m_pThemeController;

};

std::unique_ptr<Graphics::MainWindow::IMainWindowView>
createFakeMainWindowView()
{
    return std::make_unique<StubMainWindowView>();
}

}