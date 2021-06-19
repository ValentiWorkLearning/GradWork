#include "lvgl_ui.hpp"
#include "../fonts/RobotoBold40px.hpp"

#include "lvgl.h"

#include "MetaUtils.hpp"
#include "CallbackConnector.hpp"

#include "IconFont16px.hpp"

#include <random>
#include <charconv>
#include <system_error>
#include <string_view>
#include <cstdint>

#include <any>
#include <type_traits>

namespace UiConstants::Display
{
    static const std::uint32_t Width = LV_HOR_RES;
    static const std::uint32_t Height = LV_VER_RES;

}

namespace UiConstants::Theme::Dark
{
    static const lv_color_t MainDarkColor = lv_color_make(0x00, 0x33, 0x33);
    static const lv_color_t MainLightColor = lv_color_make(0x99, 0xCC, 0xCC);
}

namespace UiConstants::Theme::Light
{
    static const lv_color_t MainDarkColor = lv_color_make(0x00, 0x00, 0x00);
    static const lv_color_t MainLightColor = lv_color_make(0xFF, 0xFF, 0xFF);
}

namespace UiConstants::Theme::Pastele
{
    static const lv_color_t MainDarkColor = lv_color_make(0x00, 0x00, 0x00);
    static const lv_color_t MainLightColor = lv_color_make(0xCC, 0xCC, 0xCC);
}

namespace UiTheme = UiConstants::Theme::Pastele;

namespace
{

auto drawInyan( lv_obj_t* _parent )
{
    auto createAlignedRect = [_parent]( auto _aligmentType, const lv_style_t* _style )
    {
        lv_obj_t* pObject{ nullptr };
        pObject = lv_obj_create( _parent, nullptr );
        lv_obj_set_size(
                pObject
            ,   UiConstants::Display::Width
            ,   UiConstants::Display::Height / 2
        );

        lv_obj_set_style( pObject, _style );
        lv_obj_align( pObject, nullptr, _aligmentType, 0, 0 );

        return pObject;
    };

    static lv_style_t pInyStyle;
    static lv_style_t pYanStyle;

    lv_style_copy( &pInyStyle, &lv_style_plain_color );
    pInyStyle.body.main_color = UiTheme::MainDarkColor;
    pInyStyle.body.grad_color = pInyStyle.body.main_color;

    lv_style_copy(&pYanStyle, &lv_style_plain_color);
    pYanStyle.body.main_color = UiTheme::MainLightColor;
    pYanStyle.body.grad_color = pYanStyle.body.main_color;

    lv_obj_t* pIny = createAlignedRect(LV_ALIGN_BOTTOM_MID, &pInyStyle);
    lv_obj_t* pYan = createAlignedRect( LV_ALIGN_IN_TOP_MID, &pYanStyle );

    auto createAlignedCircle = [ _parent ](auto _aligmentType, const lv_style_t* _style)
    {
        lv_obj_t* pCircle = lv_obj_create( _parent, nullptr );

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
   
    pInyCircleStyle.body.main_color = UiTheme::MainDarkColor;
    pInyCircleStyle.body.grad_color = pInyStyle.body.main_color;
    pInyCircleStyle.body.radius = LV_RADIUS_CIRCLE;

    static lv_style_t pYanCircleStyle;

    lv_style_copy( &pYanCircleStyle, &pInyCircleStyle );
    pYanCircleStyle.body.main_color = UiTheme::MainLightColor;
    pYanCircleStyle.body.grad_color = pYanCircleStyle.body.main_color;

    lv_obj_t* pInyCircle = createAlignedCircle( LV_ALIGN_IN_RIGHT_MID, &pInyCircleStyle );
    lv_obj_t* pYanCircle = createAlignedCircle( LV_ALIGN_IN_LEFT_MID, &pYanCircleStyle );

    return std::tuple( pIny, pInyCircle, pYan, pYanCircle );
}

auto drawClocks( lv_obj_t* _parent )
{
    // Draw clocks label
    static lv_style_t hoursLabelStyle;
    lv_style_copy( &hoursLabelStyle, &lv_style_plain_color );

    lv_obj_t* pHoursLabel = lv_label_create( _parent, nullptr );
    hoursLabelStyle.text.font = &LcdNova68px;
    hoursLabelStyle.text.color = UiTheme::MainDarkColor;

    lv_label_set_style( pHoursLabel, LV_LABEL_STYLE_MAIN, &hoursLabelStyle );
    lv_obj_align(
            pHoursLabel
        ,   nullptr
        ,   LV_ALIGN_IN_LEFT_MID
        ,   UiConstants::Display::Width / 7
        ,   UiConstants::Display::Height / 30
    );

    lv_label_set_text( pHoursLabel, "22" );

    // Draw minutes label
    static lv_style_t minutesLabelStyle;
    lv_obj_t* pMinutesLabel = lv_label_create( _parent, nullptr );

    lv_style_copy( &minutesLabelStyle, &hoursLabelStyle);
    minutesLabelStyle.text.color = UiTheme::MainLightColor;

    lv_label_set_style( pMinutesLabel, LV_LABEL_STYLE_MAIN, &minutesLabelStyle );
    lv_obj_align(
            pMinutesLabel
        ,   nullptr
        ,   LV_ALIGN_CENTER
        ,   UiConstants::Display::Width / 20
        ,   UiConstants::Display::Height / 30
    );

    lv_label_set_text( pMinutesLabel, "18" );

    // Draw seconds label
    static lv_style_t secondsLabelStyle;
    lv_obj_t* pSecondsLabel = lv_label_create( _parent, nullptr );

    lv_style_copy( &secondsLabelStyle, &minutesLabelStyle );
    secondsLabelStyle.text.font = &LcdNova16px;

    lv_label_set_style( pSecondsLabel, LV_LABEL_STYLE_MAIN, &secondsLabelStyle );
    lv_obj_align(
            pSecondsLabel
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_RIGHT
        ,   0
        ,   UiConstants::Display::Height / 3 + UiConstants::Display::Height / 20
    );

    lv_label_set_text( pSecondsLabel, ":27" );

    // Draw month/day/year label
    lv_obj_t* pMmDdYearLabel = lv_label_create(_parent, nullptr);

    lv_label_set_style( pMmDdYearLabel, LV_LABEL_STYLE_MAIN, &secondsLabelStyle );
    lv_label_set_text( pMmDdYearLabel, "JAN/20/2020" );


    lv_obj_align(
            pMmDdYearLabel
        ,   nullptr
        ,   LV_ALIGN_IN_RIGHT_MID
        ,   - static_cast<int>( UiConstants::Display::Width / 8 )
        ,   static_cast<int>( UiConstants::Display::Height / 4.5f )
    );

    // Draw weeekday label
    static lv_style_t weekDayStyle;
    lv_style_copy( &weekDayStyle, &hoursLabelStyle );
    /*weekDayStyle.text.font = &LcdNova36px;*/
    weekDayStyle.text.color = UiTheme::MainDarkColor;

    lv_obj_t* pWeekDayLabel = lv_label_create( _parent, nullptr );

    lv_label_set_style( pWeekDayLabel, LV_LABEL_STYLE_MAIN, &weekDayStyle );
    lv_label_set_text( pWeekDayLabel, "MONDAY" );


    lv_obj_align(
            pWeekDayLabel
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_MID
        ,   0
        ,   UiConstants::Display::Height / 15
    );

    // Draw checked arc
    constexpr std::uint8_t ArcSize = 14;

    static lv_style_t arcCurrentStyle;
    lv_style_copy( &arcCurrentStyle, &lv_style_plain );
    arcCurrentStyle.line.color = UiTheme::MainLightColor;
    arcCurrentStyle.line.width = 2;

    lv_obj_t* pCurrentArc = lv_arc_create( _parent, nullptr );
    lv_arc_set_style( pCurrentArc, LV_ARC_STYLE_MAIN, &arcCurrentStyle );

    lv_arc_set_angles( pCurrentArc, 0, 360 );
    lv_obj_set_size( pCurrentArc, ArcSize, ArcSize );
    lv_obj_align(
            pCurrentArc
        ,   LV_ALIGN_BOTTOM_MID
        ,   -static_cast<int>( UiConstants::Display::Width / 12 )
        ,   -static_cast<int>( UiConstants::Display::Height / 10 )
    );

    // Draw unchecked arcs
    static lv_style_t pUncheckedBoxItem;

    lv_style_copy( &pUncheckedBoxItem, &lv_style_plain );
    pUncheckedBoxItem.body.main_color = UiTheme::MainLightColor;
    pUncheckedBoxItem.body.grad_color = pUncheckedBoxItem.body.main_color;
    pUncheckedBoxItem.body.radius = LV_RADIUS_CIRCLE;

    lv_obj_t* pSecondArc = lv_obj_create( _parent, nullptr );
    lv_obj_set_size( pSecondArc, ArcSize, ArcSize );
    lv_obj_set_style( pSecondArc, &pUncheckedBoxItem );
    lv_obj_align(
            pSecondArc
        ,   LV_ALIGN_BOTTOM_MID
        ,   0
        ,   -static_cast<int>( UiConstants::Display::Height / 10 )
    );

    lv_obj_t* pThirdArc = lv_obj_create( _parent, nullptr );
    lv_obj_set_size( pThirdArc, ArcSize, ArcSize );
    lv_obj_set_style( pThirdArc, &pUncheckedBoxItem );
    lv_obj_align(
            pThirdArc
        ,   LV_ALIGN_BOTTOM_MID
        ,   static_cast<int>( UiConstants::Display::Width / 12 )
        ,   -static_cast<int>( UiConstants::Display::Height / 10 )
    );


    // Draw battery icon
    lv_obj_t* batteryLabel = lv_label_create(_parent, nullptr);

    static lv_style_t iconStyleLight;
    lv_style_copy(&iconStyleLight, &hoursLabelStyle);
    iconStyleLight.text.font = &IconFont16px;
    iconStyleLight.text.color = UiTheme::MainLightColor;
    lv_obj_set_style( batteryLabel, &iconStyleLight);
    lv_label_set_text( batteryLabel, IconFontSymbols::Battery::Battery90Percent.data() );

   lv_obj_align(
            batteryLabel
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_RIGHT
        ,   -static_cast<int>( UiConstants::Display::Width / 7 )
        ,   static_cast<int>( UiConstants::Display::Height / 4 ) + static_cast<int>(UiConstants::Display::Height / 22)
    );

    // Draw battery percentage
   lv_obj_t* batteryPercentageLabel = lv_label_create(_parent, nullptr);
   lv_obj_set_style( batteryPercentageLabel, &secondsLabelStyle );
   lv_label_set_text( batteryPercentageLabel, "90%" );
   
   lv_obj_align(
            batteryPercentageLabel
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_RIGHT
        ,   -static_cast<int>(UiConstants::Display::Width / 4)
        ,   static_cast<int>(UiConstants::Display::Height / 4) + static_cast<int>(UiConstants::Display::Height / 20)
    );

   
   static lv_style_t iconStyleDark;
   lv_style_copy( &iconStyleDark, &iconStyleLight );
   iconStyleDark.text.color = UiTheme::MainDarkColor;

    // Draw bluetooth enable
   lv_obj_t* bluetoothEnable = lv_label_create( _parent, nullptr );
   lv_obj_set_style( bluetoothEnable, &iconStyleDark);
   lv_label_set_text( bluetoothEnable, IconFontSymbols::Bluetooth::BluetoothEnabled.data() );
   
   lv_obj_align(
            bluetoothEnable
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_LEFT
        ,   static_cast<int>(UiConstants::Display::Width / 6)
        ,   static_cast<int>(UiConstants::Display::Height/ 3.5f)
    );


    return std::tuple(
            pHoursLabel
        ,   pMinutesLabel
        ,   pSecondsLabel
        ,   pMmDdYearLabel
        ,   pWeekDayLabel
        ,   pCurrentArc
        ,   pSecondArc
        ,   pThirdArc
        ,   batteryLabel
        ,   batteryPercentageLabel
        ,   bluetoothEnable
    );
}

auto drawHeartrate( lv_obj_t* _parent )
{

    // Draw weeekday label
    static lv_style_t healthTitleStyle;
    lv_style_copy( &healthTitleStyle, &lv_style_plain );
    /*healthTitleStyle.text.font = &LcdNova36px;
    healthTitleStyle.text.color = UiTheme::MainDarkColor;*/

    lv_obj_t* pHealthMainLabel = lv_label_create( _parent, nullptr );

    lv_label_set_style( pHealthMainLabel, LV_LABEL_STYLE_MAIN, &healthTitleStyle);
    lv_label_set_text( pHealthMainLabel, "HEALTH" );
    lv_obj_align(
            pHealthMainLabel
        ,   nullptr
        ,   LV_ALIGN_IN_TOP_MID
        ,   0
        ,   UiConstants::Display::Height / 15
    );


    static lv_style_t iconStyleLight;
    lv_style_copy( &iconStyleLight, &lv_style_plain );
    iconStyleLight.text.font = &IconFont16px;
    iconStyleLight.text.color = UiTheme::MainLightColor;

    static lv_style_t iconStyleDark;
    lv_style_copy(&iconStyleDark, &iconStyleLight);
    iconStyleDark.text.color = UiTheme::MainDarkColor;

    
    lv_obj_t* pHeartIcon = lv_label_create( _parent, nullptr );

    lv_label_set_style( pHeartIcon, LV_LABEL_STYLE_MAIN, &iconStyleDark );
    lv_label_set_text( pHeartIcon, IconFontSymbols::Health::HeartIcon.data() );
    lv_obj_align(
            pHeartIcon
        ,   pHealthMainLabel
        ,   LV_ALIGN_OUT_BOTTOM_MID
        ,   0
        ,   0
    );

    //lv_obj_t* pHeartRateIcon = lv_img_create( _parent, nullptr );
    //lv_img_set_src( pHeartRateIcon, &HeartrateIcon );
    //lv_obj_align( pHeartRateIcon, nullptr, LV_ALIGN_IN_TOP_MID, 0, 20 );


    //static lv_style_t pHeartRateStyle;
    //lv_obj_t* pHeartRateLabel = lv_label_create( _parent, nullptr );

    //lv_style_copy( &pHeartRateStyle, &lv_style_plain_color );
    //pHeartRateStyle.text.font = &LcdNova68px;
    //pHeartRateStyle.text.color = UiTheme::MainLightColor;

    //lv_label_set_style( pHeartRateLabel, LV_LABEL_STYLE_MAIN, &pHeartRateStyle );
    //lv_obj_align(
    //        pHeartRateLabel
    //    ,   nullptr
    //    ,   LV_ALIGN_CENTER
    //    ,   0
    //    ,   UiConstants::Display::Height / 8
    //);


    //lv_label_set_text( pHeartRateLabel, "76" );

    //std::random_device randomDev;
    //std::mt19937 generator(randomDev() );

    //std::uniform_int_distribution<> dis( 60, 120 );

    //auto randomHeartrateGenerator = cbc::obtain_connector(
    //    [ pHeartRateLabel,dis, generator](lv_task_t* _pTask) mutable
    //    {
    //        std::int32_t heartRateValue{ dis( generator ) };

    //        constexpr size_t LabelSize = 4;
    //        std::array<char, LabelSize> str{};

    //        if (auto [p, ec] = std::to_chars( str.data(), str.data() + str.size(), heartRateValue );
    //            ec == std::errc())
    //        lv_label_set_text(
    //                pHeartRateLabel
    //            ,   std::string_view( str.data(), p - str.data() ).data()
    //        );
    //    }
    //);

    //lv_task_t* pTaskSwitch = lv_task_create(
    //        randomHeartrateGenerator
    //    ,   600
    //    ,   LV_TASK_PRIO_MID
    //    ,   nullptr
    //);

    return std::tuple(
            pHealthMainLabel
        ,   pHeartIcon
        /*,   pHeartRateLabel*/
    );
}

}

namespace LvglUi
{

void createWidgetsDemo()
{

    //lv_theme_t* pTheme = lv_theme_mono_init(0, nullptr);
    lv_theme_t* pTheme = lv_theme_material_init( 0, nullptr );
    lv_theme_set_current( pTheme );

    static std::array<lv_point_t, 3> validPos
        = {
                lv_point_t{ 0, 0 }
            ,   lv_point_t{ 1, 0 }
            ,   lv_point_t{ 1, 1 }
        };

    lv_obj_t* pTileView;
    pTileView = lv_tileview_create( lv_scr_act(), nullptr );
    lv_tileview_set_valid_positions(
            pTileView
        ,   validPos.data()
        ,   static_cast<std::uint16_t>( validPos.size() )
    );

    lv_tileview_set_edge_flash( pTileView, false );

    lv_obj_t* tileClock = lv_obj_create( pTileView, nullptr );
    lv_obj_set_size( tileClock, LV_HOR_RES, LV_VER_RES );
    lv_obj_set_style( tileClock, &lv_style_plain );

    auto createClockTile = [pTileView, tileClock]
    {

        /*Clock Tile: just labels*/
        auto iniYan = drawInyan( tileClock );
        auto clocks = drawClocks( tileClock );
        auto clockTileWidgets = std::tuple_cat( iniYan, clocks );
        lv_tileview_add_element( pTileView, tileClock );

        Meta::tupleApply(
                [&pTileView]( lv_obj_t* _pClockWidget )
                {
                    lv_tileview_add_element( pTileView , _pClockWidget );
                }
            ,   clockTileWidgets
        );

        return clockTileWidgets;
    };

        /*Tile2: a back menu*/
    lv_obj_t* tileHeartrate = lv_obj_create( pTileView, nullptr );
    lv_obj_set_size( tileHeartrate, LV_HOR_RES, LV_VER_RES );
    lv_obj_set_style( tileHeartrate, &lv_style_plain );
    lv_obj_set_pos( tileHeartrate, LV_HOR_RES, 0);
    lv_tileview_add_element( pTileView, tileHeartrate );

    auto heartrateCreator = [pTileView, tileHeartrate]
    {

        auto iniYanReversed = drawInyan( tileHeartrate );
        auto heartRateWidgets = drawHeartrate( tileHeartrate );
        auto heartRateTile = std::tuple_cat( iniYanReversed, heartRateWidgets );


        Meta::tupleApply(
                [&pTileView]( lv_obj_t* _pOptionsWidget )
                {
                    lv_tileview_add_element( pTileView, _pOptionsWidget );
                }
            , heartRateTile
        );

        return heartRateTile;
    };

    
    auto switcherTask = cbc::obtain_connector(
            [pTileView, heartrateCreator, createClockTile]( lv_task_t* _pTask )
        {
            static bool activeScreen{ true };
            static std::any pActiveScreenTuple;

            using THeartrateCall = std::invoke_result_t<decltype( heartrateCreator )>;
            using ClockTileCall = std::invoke_result_t<decltype( createClockTile )>;


            if( activeScreen )
            {   
                if(!pActiveScreenTuple.has_value() )
                    pActiveScreenTuple = createClockTile();
                else
                {
                    auto pSreenDeinit = std::any_cast<THeartrateCall>( pActiveScreenTuple );

                    Meta::tupleApply(
                        [](lv_obj_t* _pWidget)
                        {
                            lv_obj_del( _pWidget );
                        }
                        ,   pSreenDeinit
                    );
                    pActiveScreenTuple = createClockTile();
                }
            }
            else
            {
                if ( !pActiveScreenTuple.has_value() )
                    pActiveScreenTuple = heartrateCreator();
                else
                {
                    auto pSreenDeinit = std::any_cast< ClockTileCall>( pActiveScreenTuple );

                    Meta::tupleApply(
                        [](lv_obj_t* _pWidget)
                        {
                            lv_obj_del( _pWidget );
                        }
                        ,   pSreenDeinit
                    );
                    pActiveScreenTuple = heartrateCreator();
                }
            }
            activeScreen = !activeScreen;
            lv_tileview_set_tile_act(pTileView, activeScreen,0 , true);

        }
    );

    switcherTask(nullptr);

    lv_task_t* pTaskSwitch = lv_task_create(
            switcherTask
        ,   4500
        ,   LV_TASK_PRIO_MID
        ,   nullptr
    );
}

}
