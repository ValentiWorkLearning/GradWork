#pragma once

#include "gs_ipages_switch.hpp"
#include "gs_widget_base_obj.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

#include <string>
#include <memory>


namespace Graphics::Widgets
{

class PagesSwitch
    :   public WidgetBaseObj<IPagesSwitch>
{

public:

    explicit PagesSwitch( std::weak_ptr<Theme::IThemeController> _themeController );

    ~PagesSwitch() override = default;

public:

    void show() override;

    void hide() override;

public:

    void mapPageToIndex(std::string_view pageName, const std::uint8_t _pageIndex) override;

    void setActivePage(const std::uint8_t pageIndex) override;

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

    lv_style_t m_checkedPointStyle;
    lv_style_t m_uncheckedPointStyle;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pFirstPage;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pSecondPage;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pThirdPage;

};

std::shared_ptr<IBatteryWidget> createBatteryWidget(
    std::weak_ptr<Theme::IThemeController> _themeController
);

};