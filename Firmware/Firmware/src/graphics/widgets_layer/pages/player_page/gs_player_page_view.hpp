#pragma once

#include "gs_iplayer_page_view.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"
#include <array>

namespace Graphics::Views
{

class PlayerPage
    :   public PageViewObject<IPlayerWatchPage>
{

public:

    explicit PlayerPage( const Theme::IThemeController* _themeController );

    ~PlayerPage() override = default;

public:

    void show() override;

    void hide() override;

    void setPause() override;

    void setPlaying() override;

private:

    void initStyles();

    void initPageTitle(
            lv_obj_t* _parentObject
        ,   const std::uint32_t _displayWidth
        ,   const std::uint32_t _displayHeight
    );

private:

    lv_style_t m_mainLabelStyleDark;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pKcalTooltip;

};


std::unique_ptr<IPlayerWatchPage> createPlayerWatchView(
    const Theme::IThemeController* _themeController
);

}