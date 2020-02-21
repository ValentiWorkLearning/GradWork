#pragma once

#include "gs_page_view_object.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"

namespace Graphics::Views
{

class ClockWatch
    :   public PageViewObject
{

public:

    explicit ClockWatch( std::weak_ptr<Theme::IThemeController> _themeController );

    ~ClockWatch() override = default;

public:
    
    void show() override;

    void hide() override;

private:

    void initStyles();

    void initClockLabels(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    void initFullDateLabel(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

    void initWeekDayLabel(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

private:

    lv_style_t m_hoursLabelStyle;
    lv_style_t m_minutesLabelStyle;
    lv_style_t m_secondsLabelStyle;
    lv_style_t m_fullDateStyle;
    lv_style_t m_weekDayStyle;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pHoursLabel;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pMinutesLabel;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pSecondsLabel;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pFullDateLabel;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pWeekDayLabel;
};


std::unique_ptr<IPageViewObject> createClockWatchView(
    std::weak_ptr<Theme::IThemeController> _themeController
);

}