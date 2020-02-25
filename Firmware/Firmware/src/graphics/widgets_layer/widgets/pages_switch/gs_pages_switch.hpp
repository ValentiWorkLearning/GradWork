#pragma once

#include "gs_ipages_switch.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

#include <string>
#include <memory>


namespace Graphics::Theme
{
    class IThemeController;
}

namespace Graphics::Widgets
{

class IWidgetEventHandler;

class PagesSwitch
    :   public IPagesSwitch
{

public:

    explicit PagesSwitch( std::weak_ptr<Theme::IThemeController> _themeController );

    ~PagesSwitch() override = default;

public:

    void show() override;

    void hide() override;

    bool isVisible()const override;

private:

    void initStyles();

    void initCheckedPages(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    void initUncheckedPages(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

private:

    bool m_isVisible;

    lv_style_t m_checkedPointStyle;
    lv_style_t m_uncheckedPointStyle;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pFirstPage;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pSecondPage;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pThirdPage;

    std::weak_ptr<Theme::IThemeController> m_pThemeController;

};

std::shared_ptr<IBatteryWidget> createBatteryWidget(
    std::weak_ptr<Theme::IThemeController> _themeController
);

};