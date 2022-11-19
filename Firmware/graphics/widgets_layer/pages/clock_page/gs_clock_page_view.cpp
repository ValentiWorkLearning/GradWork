#include "gs_clock_page_view.hpp"
#include "ih/gs_itheme_controller.hpp"

namespace Graphics::Views
{

ClockWatch::ClockWatch(const Theme::IThemeController* _themeController) noexcept
    : PageViewObject<IClockWatchPage>{_themeController, IClockWatchPage::ClockPageName}
    , m_hoursLabelStyle{}
    , m_minutesLabelStyle{}
    , m_secondsLabelStyle{}
    , m_fullDateStyle{}
    , m_weekDayStyle{}
    , m_hoursValue{"00"}
    , m_minutesValue{"00"}
    , m_secondsValue{":00"}
    , m_weekdayValue{"........."}
    , m_fulldateValue{"../../...."}
{
    initStyles();
}

void ClockWatch::setHours(const std::string& _newHoursValue) noexcept
{
    m_hoursValue = _newHoursValue;
    lv_label_set_text(m_pHoursLabel.get(), m_hoursValue.c_str());
}

void ClockWatch::setMinutes(const std::string& _newMinutesValue) noexcept
{
    m_minutesValue = _newMinutesValue;
    lv_label_set_text(m_pMinutesLabel.get(), m_minutesValue.c_str());
}

void ClockWatch::setSeconds(const std::string& _newSecondsValue) noexcept
{
    m_secondsValue = _newSecondsValue;
    lv_label_set_text(m_pSecondsLabel.get(), m_secondsValue.c_str());
}

void ClockWatch::setWeekday(const std::string& _newWeekDay) noexcept
{
    m_weekdayValue = _newWeekDay;
    lv_label_set_text(m_pWeekDayLabel.get(), m_weekdayValue.c_str());
}

void ClockWatch::setFullDate(const std::string& _fullDate) noexcept
{
    m_fulldateValue = _fullDate;
    lv_label_set_text(m_pFullDateLabel.get(), m_fulldateValue.c_str());
}

void ClockWatch::resetStyle() noexcept
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { lv_style_reset(&_nodeToReset); },
        std::forward_as_tuple(
            m_hoursLabelStyle,
            m_minutesLabelStyle,
            m_secondsLabelStyle,
            m_fullDateStyle,
            m_weekDayStyle));
}

void ClockWatch::initStyles() noexcept
{
    auto pThemeProvider = PageViewObject::getThemeController();
    if (!pThemeProvider)
        return;

    m_hoursLabelStyle =
        pThemeProvider->getFontStyle(Theme::FontSize::x_large, Theme::Color::MainThemeDark);

    m_minutesLabelStyle =
        pThemeProvider->getFontStyle(Theme::FontSize::x_large, Theme::Color::MainThemeLight);

    m_secondsLabelStyle =
        pThemeProvider->getFontStyle(Theme::FontSize::small, Theme::Color::MainThemeLight);

    m_fullDateStyle =
        pThemeProvider->getFontStyle(Theme::FontSize::small, Theme::Color::MainThemeLight);
    ;

    m_weekDayStyle =
        pThemeProvider->getFontStyle(Theme::FontSize::large, Theme::Color::MainThemeDark);
}

void ClockWatch::initPageWidgets(
    lv_obj_t* _parent,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    initClockLabels(_parent, _displayWidth, _displayHeight);
    initFullDateLabel(_parent, _displayWidth, _displayHeight);
    initWeekDayLabel(_parent, _displayWidth, _displayHeight);

    restoreLabelsText();
}

void ClockWatch::unloadWidgets() noexcept
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { _nodeToReset.reset(); },
        std::forward_as_tuple(
            m_pHoursLabel, m_pMinutesLabel, m_pSecondsLabel, m_pFullDateLabel, m_pWeekDayLabel));
}

void ClockWatch::initClockLabels(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    auto parent = _parentObject;
    const std::uint32_t DisplayWidth{_displayWidth};
    const std::uint32_t DisplayHeight{_displayHeight};

    m_pHoursLabel.reset(lv_label_create(parent));
    lv_obj_add_style(m_pHoursLabel.get(), &m_hoursLabelStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_align(m_pHoursLabel.get(), LV_ALIGN_LEFT_MID, DisplayWidth / 7, DisplayHeight / 30);

    m_pMinutesLabel.reset(lv_label_create(parent));
    lv_obj_add_style(m_pMinutesLabel.get(), &m_minutesLabelStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_align(m_pMinutesLabel.get(), LV_ALIGN_CENTER, DisplayWidth / 5, DisplayHeight / 30);

    m_pSecondsLabel.reset(lv_label_create(parent));
    lv_obj_add_style(m_pSecondsLabel.get(), &m_secondsLabelStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_align(
        m_pSecondsLabel.get(),
        LV_ALIGN_TOP_RIGHT,
        -static_cast<std::int16_t>(DisplayWidth / 12),
        DisplayHeight / 3 + DisplayHeight / 20);
}

void ClockWatch::initFullDateLabel(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{

    m_pFullDateLabel.reset(lv_label_create(_parentObject));
    lv_obj_add_style(m_pFullDateLabel.get(), &m_fullDateStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_align(
        m_pFullDateLabel.get(),
        LV_ALIGN_RIGHT_MID,
        -static_cast<int>(_displayWidth / 15),
        static_cast<int>(_displayHeight / 4.5f));
}

void ClockWatch::initWeekDayLabel(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pWeekDayLabel.reset(lv_label_create(_parentObject));
    lv_obj_add_style(m_pWeekDayLabel.get(), &m_weekDayStyle, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_align(m_pWeekDayLabel.get(), LV_ALIGN_TOP_MID, 0, _displayHeight / 15);
}

void ClockWatch::restoreLabelsText() noexcept
{
    lv_label_set_text(m_pHoursLabel.get(), m_hoursValue.c_str());
    lv_label_set_text(m_pMinutesLabel.get(), m_minutesValue.c_str());
    lv_label_set_text(m_pSecondsLabel.get(), m_secondsValue.c_str());
    lv_label_set_text(m_pFullDateLabel.get(), m_fulldateValue.c_str());
    lv_label_set_text(m_pWeekDayLabel.get(), m_weekdayValue.c_str());
}

std::unique_ptr<IClockWatchPage> createClockWatchView(
    const Theme::IThemeController* _themeController) noexcept
{
    return std::make_unique<ClockWatch>(_themeController);
}

} // namespace Graphics::Views