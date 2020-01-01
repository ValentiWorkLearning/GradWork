#include "lvgl_ui.hpp"

#include <cstdint>

#pragma warning( push, 0 )
#pragma warning( disable : 4576 )

extern "C"
{
    #include "lvgl.h"
}

#pragma warning( pop )

namespace UiConstants::Display
{
    static const std::uint32_t Width = LV_HOR_RES;
    static const std::uint32_t Height = LV_VER_RES;
}

namespace
{

void drawInyan()
{
    auto createAlignedRect = []( auto _aligmentType, const lv_style_t* _style )
    {
        lv_obj_t* pObject{ nullptr };
        pObject = lv_obj_create( lv_scr_act(), nullptr );
        lv_obj_set_size(
            pObject
            , UiConstants::Display::Width / 2
            , UiConstants::Display::Height
        );

        lv_obj_set_style( pObject, _style );
        lv_obj_align( pObject, nullptr, _aligmentType, 0, 0 );

        return pObject;
    };

    static lv_style_t pInyStyle;
    static lv_style_t pYanStyle;

    lv_style_copy( &pInyStyle, &lv_style_plain_color );
    pInyStyle.body.main_color = lv_color_make( 0x00,0x00,0x00 );
    pInyStyle.body.grad_color = pInyStyle.body.main_color;

    lv_style_copy(&pYanStyle, &lv_style_plain_color);
    pYanStyle.body.main_color = lv_color_make( 0xFF, 0xFF, 0xFF );
    pYanStyle.body.grad_color = pYanStyle.body.main_color;

    lv_obj_t* pIny = createAlignedRect( LV_ALIGN_IN_RIGHT_MID, &pInyStyle );
    lv_obj_t* pYan = createAlignedRect( LV_ALIGN_IN_LEFT_MID, &pYanStyle );


    auto createAlignedCircle = [](auto _aligmentType, const lv_style_t* _style)
    {
        lv_obj_t* pCircle = lv_obj_create(lv_scr_act(), nullptr);

        lv_obj_set_size(
                pCircle
            ,   UiConstants::Display::Width / 2
            ,   UiConstants::Display::Height / 2
        );

        lv_obj_set_style( pCircle, _style );
        lv_obj_align( pCircle, nullptr, _aligmentType, 0, 0);

        return pCircle;
    };

    static lv_style_t pInyCircleStyle;
    lv_style_copy( &pInyCircleStyle, &lv_style_plain_color );
   
    pInyCircleStyle.body.main_color = lv_color_make(0x00, 0x00, 0x00);
    pInyCircleStyle.body.grad_color = pInyStyle.body.main_color;
    pInyCircleStyle.body.radius = LV_RADIUS_CIRCLE;

    static lv_style_t pYanCircleStyle;

    lv_style_copy( &pYanCircleStyle, &pInyCircleStyle );
    pYanCircleStyle.body.main_color = lv_color_make(0xFF, 0xFF, 0xFF);
    pYanCircleStyle.body.grad_color = pYanCircleStyle.body.main_color;

    lv_obj_t* pInyCircle = createAlignedCircle( LV_ALIGN_IN_BOTTOM_MID, &pInyCircleStyle );
    lv_obj_t* pYanCircle = createAlignedCircle( LV_ALIGN_IN_TOP_MID, &pYanCircleStyle );

}

}

namespace LvglUi
{

void createWidgetsDemo()
{

    //lv_theme_t* pTheme = lv_theme_mono_init(0, nullptr);
    lv_theme_t* pTheme = lv_theme_material_init(0, nullptr);
    lv_theme_set_current(pTheme);

    lv_obj_t* pScreen = lv_disp_get_scr_act(nullptr);     /*Get the current screen*/

    drawInyan();

  /*  lv_obj_t * preload = lv_preload_create(lv_scr_act(), nullptr);
    lv_preload_set_spin_time(preload, 10000);
    lv_obj_set_size(preload, 240, 240);
    lv_obj_align(preload, nullptr, LV_ALIGN_CENTER, 0, 0);*/


    static lv_style_t hoursLabelStyle;
    lv_style_copy( &hoursLabelStyle, &lv_style_transp_tight );         /*Copy a built-in style as a starting point*/

    lv_obj_t* pHoursLabel = lv_label_create( pScreen, nullptr );
    hoursLabelStyle.text.font = &lv_font_roboto_28;

    lv_label_set_style( pHoursLabel, LV_LABEL_STYLE_MAIN, &hoursLabelStyle );
    lv_obj_align(
            pHoursLabel
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_MID
        ,   UiConstants::Display::Width / 8
        ,   UiConstants::Display::Height / 3
    );

    lv_label_set_text( pHoursLabel, "11" );


    static lv_style_t minutesLabelStyle;
    lv_obj_t* pMinutesLabel = lv_label_create( pScreen, nullptr );

    lv_style_copy( &minutesLabelStyle, &lv_style_transp_tight );
    minutesLabelStyle.text.font = &lv_font_roboto_28;
    minutesLabelStyle.text.color = lv_color_make(0xFF, 0xFF, 0xFF);

    lv_label_set_style( pMinutesLabel, LV_LABEL_STYLE_MAIN, &minutesLabelStyle );
    lv_obj_align(
            pMinutesLabel
        ,   nullptr
        ,   LV_ALIGN_CENTER
        ,   UiConstants::Display::Width / 8
        ,   UiConstants::Display::Height / 8
    );

    lv_label_set_text( pMinutesLabel, "27" );


    static lv_style_t secondsLabelStyle;
    lv_obj_t* pSecondsLabel = lv_label_create( pScreen, nullptr );

    lv_style_copy( &secondsLabelStyle, &minutesLabelStyle );
    secondsLabelStyle.text.font = &lv_font_roboto_16;

    lv_label_set_style( pSecondsLabel, LV_LABEL_STYLE_MAIN, &secondsLabelStyle );
    lv_obj_align(
            pSecondsLabel
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_RIGHT
        ,   0
        ,   UiConstants::Display::Height / 3 + UiConstants::Display::Height / 24
    );

    lv_label_set_text( pSecondsLabel, "27" );
}

}