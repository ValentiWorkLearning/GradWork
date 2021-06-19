#pragma once

#include "ih/pages/gs_iplayer_page_view.hpp"
#include "widgets_layer/gs_page_view_object.hpp"

#include "lvgl.h"

#include "utils/MetaUtils.hpp"

#include <array>

namespace Graphics::Views
{

class PlayerPage : public PageViewObject<IPlayerWatchPage>
{

public:
    explicit PlayerPage(const Theme::IThemeController* _themeController) noexcept;

    ~PlayerPage() override = default;

public:
    void setPause() noexcept override;

    void setPlaying() noexcept override;

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

    void initPlayIcon(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

    void initNextSongIcon(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

    void initPrevSongIcon(
        lv_obj_t* _parentObject,
        const std::uint32_t _displayWidth,
        const std::uint32_t _displayHeight) noexcept;

private:
    lv_style_t m_mainLabelStyleDark;
    lv_style_t m_melodyIconStyle;
    lv_style_t m_playIconStyleDark;
    lv_style_t m_playIconStyleLight;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pageTitle;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_melodyIcon;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pPlayIconFirst;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pPlayIconSecond;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pSwitchPreviousSongArrow;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pSwitchPreviousSongLine;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pSwitchNextSongArrow;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pSwitchNextSongLine;
};

std::unique_ptr<IPlayerWatchPage> createPlayerWatchView(
    const Theme::IThemeController* _themeController) noexcept;

} // namespace Graphics::Views
