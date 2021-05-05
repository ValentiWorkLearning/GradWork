#pragma once

#include "ih/pages/gs_iclock_page_view.hpp"
#include "widgets_layer/gs_page_view_object.hpp"

#include "lvgl.h"

#include "utils/MetaUtils.hpp"

namespace Graphics::Views
{

class ClockWatch
    :   public PageViewObject<IClockWatchPage>
{

public:

    explicit ClockWatch( const Theme::IThemeController* _themeController )noexcept;

    ~ClockWatch() override = default;

public:

    void setHours( const std::string& _newHoursValue )noexcept override;

    void setMinutes( const std::string& _newMinutesValue )noexcept override;

    void setSeconds( const std::string& _newSecondsValue )noexcept override;

    void setWeekday( std::string_view _newWeekDay )noexcept override;

    void setFullDate( const std::string& _fullDate )noexcept override;

protected:

    void resetStyle()noexcept override;

    void initStyles()noexcept override;

    void initPageWidgets(
            lv_obj_t* _parent
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    )noexcept override;

    void unloadWidgets()noexcept override;

private:

    void initClockLabels(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    )noexcept;

    void initFullDateLabel(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    )noexcept;

    void initWeekDayLabel(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    )noexcept;

    void restoreLabelsText()noexcept;

private:

    lv_style_t m_hoursLabelStyle;
    lv_style_t m_minutesLabelStyle;
    lv_style_t m_secondsLabelStyle;
    lv_style_t m_fullDateStyle;
    lv_style_t m_weekDayStyle;

    std::string m_hoursValue;
    std::string m_minutesValue;
    std::string m_secondsValue;
    std::string m_weekdayValue;
    std::string m_fulldateValue;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pHoursLabel;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pMinutesLabel;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pSecondsLabel;

    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pFullDateLabel;
    Meta::PointerWrapper<lv_obj_t,lv_obj_del> m_pWeekDayLabel;
};


std::unique_ptr<IClockWatchPage> createClockWatchView(
    const Theme::IThemeController* _themeController
)noexcept;

}
