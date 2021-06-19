#pragma once

#include "ih/pages/gs_ihealth_page_view.hpp"
#include "widgets_layer/gs_page_view_object.hpp"

#include "lvgl.h"

#include "utils/MetaUtils.hpp"

#include <array>

namespace Graphics::Views
{

class HealthPage : public PageViewObject<IHealthWatchPage>
{

public:
    explicit HealthPage(const Theme::IThemeController* _themeController) noexcept;

    ~HealthPage() override = default;

public:
    void setStepsCount(std::uint8_t _newStepsValue) noexcept override;

    void setHeartrate(std::uint8_t _newHeartrateValue) noexcept override;

    void setCalloriesCount(std::uint8_t _newCalloriesCount) noexcept override;

protected:
    void resetStyle() noexcept override;

    void initStyles() noexcept override;

    void initPageWidgets(
        lv_obj_t* _parent,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept override;

    void unloadWidgets() noexcept override;

private:
    void initPageTitle(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

    void initHeartrateWidgets(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

    void initCalloriesCounter(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

    void initStepsCounter(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

private:
    static constexpr std::size_t PointsCount = 6;
    static constexpr std::uint8_t LineWidth = 3;
    static constexpr std::uint8_t LineRounded = 2;

    static inline std::array<lv_point_t, PointsCount> CardioIconPoints = {
        lv_point_t{7, 20},
        lv_point_t{15, 20},
        lv_point_t{20, 0},
        lv_point_t{30, 40},
        lv_point_t{35, 20},
        lv_point_t{42, 20}};

private:
    lv_style_t m_mainLabelStyleDark;
    lv_style_t m_healthPageIconStyle;

    lv_style_t m_mainFontLight;
    lv_style_t m_mainFontDark;
    lv_style_t m_tooltipsStyleDark;
    lv_style_t m_tooltipsStyleLight;
    lv_style_t m_stepsIconStyle;

    lv_style_t m_pulseLineStyle;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pHealthPageLabel;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pHealthPageIcon;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pHeartBeatsLabel;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pHeartBeatsTooltip;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pHeartBeatsIcon;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pPulseIcon;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pStepsLabel;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pStepsIcon;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pStepsTooltip;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pKcalLabel;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pKcalTooltip;
};

std::unique_ptr<IHealthWatchPage> createHeartrateWatchView(
    const Theme::IThemeController* _themeController) noexcept;

} // namespace Graphics::Views
