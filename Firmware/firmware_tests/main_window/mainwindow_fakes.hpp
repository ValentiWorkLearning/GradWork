#pragma once

#include <gmock/gmock.h>

#include "ih/gs_imain_window.hpp"
#include "ih/gs_itheme_controller.hpp"

#include <string>

namespace Graphics::Theme
{

class StubThemeController : public IThemeController
{

    void setActiveTheme(ColorTheme _themeToSet) noexcept override
    {
    }

    ColorTheme getActiveTheme() const noexcept override
    {
        return Graphics::Theme::ColorTheme::Pastele;
    }

public:
    lv_style_t getIconsFont(FontSize _fontStyle, Color _fontColor) const noexcept override
    {
        lv_style_t stubFont{};
        return stubFont;
    }

    lv_style_t getFontStyle(FontSize _fontStyle, Color _fontColor) const noexcept override
    {
        lv_style_t stubFont{};
        return stubFont;
    }

    lv_color_t getMainThemeColor(Color _fontColor) const noexcept override
    {
        return lv_color_make(0xFF, 0xFF, 0xFF);
    }

    std::uint32_t getDisplayWidth() const noexcept override
    {
        return 240;
    }

    std::uint32_t getDisplayHeight() const noexcept override
    {
        return 240;
    }

public:
    ~StubThemeController() override = default;
};

std::unique_ptr<IThemeController> createStubThemeController() noexcept
{
    return std::make_unique<StubThemeController>();
}

} // namespace Graphics::Theme

namespace Graphics::StubMainWindow
{

class StubMainWindowView : public Graphics::MainWindow::IMainWindowView
{

public:
    StubMainWindowView() noexcept : m_pThemeController{Graphics::Theme::createStubThemeController()}
    {
    }

    virtual ~StubMainWindowView() = default;

public:
    void initBackground() noexcept override
    {
    }

    void resetBackgroundStyle() noexcept override
    {
    }

public:
    const Theme::IThemeController* getThemeController() const noexcept override
    {
        return m_pThemeController.get();
    }

    Theme::IThemeController* getThemeController() noexcept override
    {
        return m_pThemeController.get();
    }

private:
    std::unique_ptr<Theme::IThemeController> m_pThemeController;
};

std::unique_ptr<Graphics::MainWindow::IMainWindowView> createFakeMainWindowView() noexcept
{
    return std::make_unique<StubMainWindowView>();
}

} // namespace Graphics::StubMainWindow