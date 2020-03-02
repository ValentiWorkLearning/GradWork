#pragma once

#include "gs_ihealth_page_view.hpp"
#include "gs_page_view_object.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

namespace Graphics::Views
{

class HealthPage
    :   public PageViewObject<IHealthWatchPage>
{

public:

    explicit HealthPage( std::weak_ptr<Theme::IThemeController> _themeController );

    ~HealthPage() override = default;

public:

    void show() override;

    void hide() override;

    void setStepsCount(std::uint8_t _newStepsValue) override;

    void setHeartrate(std::uint8_t _newHeartrateValue) override;

    void setCalloriesCount(std::uint8_t _newCalloriesCount) override;

private:

    void initStyles();

    void initPageTitle(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    void initHeartrateWidgets(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    void initCalloriesCounter(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    void initStepsCounter(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

private:

    lv_style_t m_mainLabelStyleDark;
    lv_style_t m_mainLabelStyleLight;
    lv_style_t m_healthPageIconStyle;

    lv_style_t m_mainFontLight;
    lv_style_t m_mainFontDark;
    lv_style_t m_tooltipsStyleDark;
    lv_style_t m_tooltipsStyleLight;
    lv_style_t m_stepsIconStyle;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pHealthPageLabel;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pHealthPageIcon;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pHeartBeatsLabel;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pHeartBeatsTooltip;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pHeartBeatsIcon;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pStepsLabel;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pStepsIcon;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pStepsTooltip;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pKcalLabel;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pKcalTooltip;

};


std::shared_ptr<IHealthWatchPage> createHeartrateWatchView(
    std::weak_ptr<Theme::IThemeController> _themeController
);

}