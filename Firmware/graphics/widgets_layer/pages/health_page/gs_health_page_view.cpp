#include "gs_health_page_view.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "fonts/IconFont16px.hpp"
#include "fonts/IconFont35px.hpp"

namespace Graphics::Views
{

HealthPage::HealthPage(const Theme::IThemeController* _themeController) noexcept
    : PageViewObject<IHealthWatchPage>{_themeController, IHealthWatchPage::HealthPageName}
    , m_mainLabelStyleDark{}
    , m_healthPageIconStyle{}
    , m_mainFontLight{}
    , m_mainFontDark{}
    , m_tooltipsStyleDark{}
    , m_tooltipsStyleLight{}
    , m_stepsIconStyle{}
    , m_pulseLineStyle{}
{
}

void HealthPage::initPageWidgets(
    lv_obj_t* _parent,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    initHeartrateWidgets(_parent, _displayWidth, _displayHeight);
    initCalloriesCounter(_parent, _displayWidth, _displayHeight);
    initStepsCounter(_parent, _displayWidth, _displayHeight);
    initPageTitle(_parent, _displayWidth, _displayHeight);
}

void HealthPage::unloadWidgets() noexcept
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { _nodeToReset.reset(); },
        std::forward_as_tuple(
            m_pHealthPageLabel,
            m_pHealthPageIcon,
            m_pHeartBeatsLabel,
            m_pHeartBeatsTooltip,
            m_pPulseIcon,
            m_pStepsLabel,
            m_pStepsTooltip,
            m_pStepsIcon,
            m_pKcalLabel,
            m_pKcalTooltip));
}

void HealthPage::setStepsCount(std::uint8_t _newStepsValue) noexcept
{
}

void HealthPage::setHeartrate(std::uint8_t _newHeartrateValue) noexcept
{
}

void HealthPage::setCalloriesCount(std::uint8_t _newCalloriesCount) noexcept
{
}

void HealthPage::initStyles() noexcept
{
    auto pThemeProvider = PageViewObject::getThemeController();
    if (!pThemeProvider)
        return;

    m_mainLabelStyleDark =
        pThemeProvider->getFontStyle(Theme::FontSize::large, Theme::Color::MainThemeDark);

    m_mainFontDark =
        pThemeProvider->getFontStyle(Theme::FontSize::normal, Theme::Color::MainThemeDark);

    m_mainFontLight =
        pThemeProvider->getFontStyle(Theme::FontSize::normal, Theme::Color::MainThemeLight);

    m_healthPageIconStyle =
        pThemeProvider->getIconsFont(Theme::FontSize::small, Theme::Color::MainThemeDark);

    m_stepsIconStyle =
        pThemeProvider->getIconsFont(Theme::FontSize::normal, Theme::Color::MainThemeLight);

    m_tooltipsStyleDark =
        pThemeProvider->getFontStyle(Theme::FontSize::extra_small, Theme::Color::MainThemeDark);

    m_tooltipsStyleLight =
        pThemeProvider->getFontStyle(Theme::FontSize::extra_small, Theme::Color::MainThemeLight);

    auto MainThemeDark = pThemeProvider->getMainThemeColor(Theme::Color::MainThemeDark);

    lv_style_init(&m_pulseLineStyle);
    lv_style_set_line_color(&m_pulseLineStyle, MainThemeDark);

    constexpr int LineWidth = 3;
    lv_style_set_line_width(&m_pulseLineStyle, LineWidth);
    lv_style_set_line_rounded(&m_pulseLineStyle, true);
}

void HealthPage::resetStyle() noexcept
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { lv_style_reset(&_nodeToReset); },
        std::forward_as_tuple(
            m_mainLabelStyleDark,
            m_healthPageIconStyle,
            m_mainFontLight,
            m_mainFontDark,
            m_tooltipsStyleDark,
            m_tooltipsStyleLight,
            m_stepsIconStyle,
            m_pulseLineStyle));
}

void HealthPage::initPageTitle(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pHealthPageLabel.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pHealthPageLabel.get(), &m_mainLabelStyleDark, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pHealthPageLabel.get(), "HEALTH");
    lv_obj_align(m_pHealthPageLabel.get(), LV_ALIGN_TOP_MID, 0, _displayHeight / 15);

    m_pHealthPageIcon.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pHealthPageIcon.get(), &m_healthPageIconStyle, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pHealthPageIcon.get(), IconFontSymbols::Health::HeartIcon.data());
    lv_obj_align_to(
        m_pHealthPageIcon.get(), m_pHealthPageLabel.get(), LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
}

void HealthPage::initHeartrateWidgets(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pHeartBeatsLabel.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_pHeartBeatsLabel.get(), &m_mainFontDark, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pHeartBeatsLabel.get(), "80");

    lv_obj_align(
        m_pHeartBeatsLabel.get(),
        LV_ALIGN_LEFT_MID,
        _displayWidth / 4 - _displayWidth / 60,
        -static_cast<int>(_displayHeight / 24));

    m_pHeartBeatsTooltip.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pHeartBeatsTooltip.get(), &m_tooltipsStyleDark, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pHeartBeatsTooltip.get(), "HEARTBEATS");

    lv_obj_align_to(
        m_pHeartBeatsTooltip.get(), m_pHeartBeatsLabel.get(), LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    m_pPulseIcon.reset(lv_line_create(_parentObject));

    lv_line_set_points(
        m_pPulseIcon.get(),
        CardioIconPoints.data(),
        static_cast<std::uint16_t>(CardioIconPoints.size()));

    lv_obj_add_style(m_pPulseIcon.get(), &m_pulseLineStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_align(m_pPulseIcon.get(), LV_ALIGN_LEFT_MID, 0, -static_cast<int>(_displayHeight / 25));
}

void HealthPage::initCalloriesCounter(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pKcalLabel.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_pKcalLabel.get(), &m_mainFontLight, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pKcalLabel.get(), "160");

    lv_obj_align(
        m_pKcalLabel.get(),
        LV_ALIGN_CENTER,
        _displayWidth / 6,
        static_cast<int>(_displayHeight / 6));

    m_pKcalTooltip.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_pKcalTooltip.get(), &m_tooltipsStyleLight, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pKcalTooltip.get(), "KCAL");

    lv_obj_align_to(
        m_pKcalTooltip.get(), m_pKcalLabel.get(), LV_ALIGN_OUT_BOTTOM_RIGHT, _displayWidth / 10, 0);
}

void HealthPage::initStepsCounter(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pStepsLabel.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_pStepsLabel.get(), &m_mainFontLight, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pStepsLabel.get(), "3600");

    lv_obj_align(
        m_pStepsLabel.get(),
        LV_ALIGN_RIGHT_MID,
        -static_cast<int>(_displayWidth / 12),
        -static_cast<int>(_displayHeight / 20));

    m_pStepsTooltip.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_pStepsTooltip.get(), &m_tooltipsStyleLight, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pStepsTooltip.get(), "STEPS");

    lv_obj_align_to(
        m_pStepsTooltip.get(),
        m_pStepsLabel.get(),
        LV_ALIGN_OUT_BOTTOM_RIGHT,
        _displayWidth / 24,
        0);

    m_pStepsIcon.reset(lv_label_create(_parentObject));
    lv_obj_add_style(m_pStepsIcon.get(), &m_stepsIconStyle, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pStepsIcon.get(), IconFontSymbols::Steps::StepsIcon.data());

    lv_obj_align(
        m_pStepsIcon.get(),
        LV_ALIGN_CENTER,
        static_cast<int>(_displayWidth / 10),
        -static_cast<int>(_displayHeight / 48));
}

std::unique_ptr<IHealthWatchPage> createHeartrateWatchView(
    const Theme::IThemeController* _themeController) noexcept
{
    return std::make_unique<HealthPage>(_themeController);
}

} // namespace Graphics::Views
