#include "gs_player_page_view.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "utils/MetaUtils.hpp"

#include "fonts/IconFont24px.hpp"
#include "fonts/PlayerIcons68px.hpp"

namespace Graphics::Views
{

PlayerPage::PlayerPage(const Theme::IThemeController* _themeController) noexcept
    : PageViewObject<IPlayerWatchPage>{_themeController, IPlayerWatchPage::PlayerPageName}
    , m_mainLabelStyleDark{}
    , m_melodyIconStyle{}
    , m_playIconStyleDark{}
    , m_playIconStyleLight{}
{
    initStyles();
}

void PlayerPage::setPause() noexcept
{
}

void PlayerPage::setPlaying() noexcept
{
}

void PlayerPage::resetStyle() noexcept
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { lv_style_reset(&_nodeToReset); },
        std::forward_as_tuple(
            m_mainLabelStyleDark, m_melodyIconStyle, m_playIconStyleDark, m_playIconStyleLight));
}

void PlayerPage::initStyles() noexcept
{
    auto pThemeProvider = PageViewObject::getThemeController();
    if (!pThemeProvider)
        return;

    m_mainLabelStyleDark =
        pThemeProvider->getFontStyle(Theme::FontSize::below_normal, Theme::Color::MainThemeDark);

    m_melodyIconStyle = m_playIconStyleDark =
        pThemeProvider->getIconsFont(Theme::FontSize::below_normal, Theme::Color::MainThemeDark);

    m_playIconStyleDark =
        pThemeProvider->getIconsFont(Theme::FontSize::large, Theme::Color::MainThemeDark);
    m_playIconStyleLight =
        pThemeProvider->getIconsFont(Theme::FontSize::large, Theme::Color::MainThemeLight);
}

void PlayerPage::initPageWidgets(
    lv_obj_t* _parent,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    initPageTitle(_parent, _displayWidth, _displayHeight);
    initPlayIcon(_parent, _displayWidth, _displayHeight);
    initPrevSongIcon(_parent, _displayWidth, _displayHeight);
    initNextSongIcon(_parent, _displayWidth, _displayHeight);
}

void PlayerPage::unloadWidgets() noexcept
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { _nodeToReset.reset(); },
        std::forward_as_tuple(
            m_pageTitle,
            m_melodyIcon,
            m_pPlayIconFirst,
            m_pPlayIconSecond,
            m_pSwitchPreviousSongArrow,
            m_pSwitchPreviousSongLine,
            m_pSwitchNextSongArrow,
            m_pSwitchNextSongLine));
}

void PlayerPage::initPageTitle(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pageTitle.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_pageTitle.get(), &m_mainLabelStyleDark, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pageTitle.get(), "MUSIC");
    lv_obj_align(m_pageTitle.get(), LV_ALIGN_TOP_MID, 0, _displayHeight / 6);

    m_melodyIcon.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_melodyIcon.get(), &m_melodyIconStyle, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_melodyIcon.get(), IconFontSymbols::Music::Melody.data());
    lv_obj_align(m_melodyIcon.get(), LV_ALIGN_TOP_MID, 0, _displayHeight / 30);
}

void PlayerPage::initPlayIcon(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{

    m_pPlayIconSecond.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pPlayIconSecond.get(), &m_playIconStyleLight, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pPlayIconSecond.get(), IconFontSymbols::Player::SecondPart.data());
    lv_obj_align(m_pPlayIconSecond.get(), LV_ALIGN_CENTER, 6, 0);

    m_pPlayIconFirst.reset(lv_label_create(_parentObject));

    lv_obj_add_style(m_pPlayIconFirst.get(), &m_playIconStyleDark, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pPlayIconFirst.get(), IconFontSymbols::Player::FirstPart.data());
    lv_obj_align(
        m_pPlayIconFirst.get(), LV_ALIGN_LEFT_MID, _displayWidth / 3 + _displayWidth / 25, 0);
}

void PlayerPage::initNextSongIcon(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pSwitchNextSongArrow.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pSwitchNextSongArrow.get(), &m_playIconStyleLight, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pSwitchNextSongArrow.get(), IconFontSymbols::Player::ArrowRight.data());
    lv_obj_align(m_pSwitchNextSongArrow.get(), LV_ALIGN_CENTER, _displayWidth / 3, 0);

    m_pSwitchNextSongLine.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pSwitchNextSongLine.get(), &m_playIconStyleLight, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pSwitchNextSongLine.get(), IconFontSymbols::Player::Line.data());
    lv_obj_align(m_pSwitchNextSongLine.get(), LV_ALIGN_CENTER, _displayWidth / 5, 0);
}

void PlayerPage::initPrevSongIcon(
    lv_obj_t* _parentObject,
    const std::uint32_t _displayWidth,
    const std::uint32_t _displayHeight) noexcept
{
    m_pSwitchPreviousSongArrow.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pSwitchPreviousSongArrow.get(), &m_playIconStyleDark, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pSwitchPreviousSongArrow.get(), IconFontSymbols::Player::ArrowLeft.data());
    lv_obj_align(m_pSwitchPreviousSongArrow.get(), LV_ALIGN_LEFT_MID, _displayWidth / 20, 0);

    m_pSwitchPreviousSongLine.reset(lv_label_create(_parentObject));

    lv_obj_add_style(
        m_pSwitchPreviousSongLine.get(), &m_playIconStyleDark, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_text(m_pSwitchPreviousSongLine.get(), IconFontSymbols::Player::Line.data());
    lv_obj_align(m_pSwitchPreviousSongLine.get(), LV_ALIGN_LEFT_MID, _displayWidth / 10, 0);
}

std::unique_ptr<IPlayerWatchPage> createPlayerWatchView(
    const Theme::IThemeController* _themeController) noexcept
{
    return std::make_unique<PlayerPage>(_themeController);
}

} // namespace Graphics::Views
