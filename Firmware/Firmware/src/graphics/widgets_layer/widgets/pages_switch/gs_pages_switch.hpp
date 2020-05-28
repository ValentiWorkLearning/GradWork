#pragma once

#include "ih/widgets/gs_ipages_switch.hpp"
#include "widgets_layer/widgets/gs_widget_base_obj.hpp"

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

class PagesSwitch
    :   public WidgetBaseObj<IPagesSwitch>
{

public:

    explicit PagesSwitch( const Theme::IThemeController* _themeController );

    ~PagesSwitch() override = default;

public:

    void show() override;

    void hide() override;

    void reloadStyle()override;

public:

    void setActivePage( std::string_view _pageName ) override;

private:

    void initStyles();

    void resetStyle();

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

    static constexpr inline std::uint8_t ArcSize = 16;

private:

    lv_style_t m_pointStyle;

    std::string_view m_activePageName;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pFirstPage;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pSecondPage;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pThirdPage;

};

std::unique_ptr<IPagesSwitch> createPagesSwitch(
    const Theme::IThemeController* _themeController
);

};
