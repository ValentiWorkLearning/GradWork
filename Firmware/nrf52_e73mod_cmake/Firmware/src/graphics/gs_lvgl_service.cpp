#include "gs_lvgl_service.hpp"

#include "lvgl.h"

#include "CallbackConnector.hpp"
#include "logger_service.hpp"

#include "nrf_delay.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"

namespace
{
    APP_TIMER_DEF(m_gfxEllapsedTimerId);
}

namespace Graphics
{

LvglGraphicsService::LvglGraphicsService(
        std::unique_ptr<DisplayDriver::IDisplayDriver>&& _hardwareDriver
        )   :   m_hardwareDisplayDriver{ std::move( _hardwareDriver ) }
{
    initLvglLogger();
    lv_init();
    
    lv_disp_buf_init(
                    &displayBuffer
                ,   &dispFrameBufFirst
                ,   &dispFrameBufSecond
                ,   DispHorRes
            );

    lv_disp_drv_init( &m_glDisplayDriver );
    m_glDisplayDriver.buffer = &displayBuffer;

    auto hardwareDriverCallback = cbc::obtain_connector(
      [ this ]( lv_disp_drv_t* _displayDriver, const lv_area_t* _fillArea, lv_color_t* _colorFill )
      {
            m_hardwareDisplayDriver->fillRectangle(
                    _fillArea->x1
                ,   _fillArea->y1
                ,   _fillArea->x2
                ,   _fillArea->y2
                ,   reinterpret_cast<std::uint16_t*>( _colorFill )
            );
      }
    );

    m_glDisplayDriver.flush_cb = hardwareDriverCallback;

    m_glDisplay = lv_disp_drv_register( &m_glDisplayDriver );

    m_hardwareDisplayDriver->onRectArreaFilled.connect(
        [this]
        {
            lv_disp_flush_ready( &m_glDisplayDriver );
            //lv_log_add( LV_LOG_LEVEL_TRACE, __FILE__, __LINE__, "display flush ready" );
        }
    );

    initGfxTimer();
}

void LvglGraphicsService::executeGlTask()
{
    lv_task_handler();
}

void LvglGraphicsService::initGfxTimer()
{
    ret_code_t errorCode{};

    auto gfxTimerCallback = cbc::obtain_connector(
        [ this ]( void * _pContext )
        {
            lv_tick_inc( LvglNotificationTime );
        }
    );

    errorCode = app_timer_create(
                &m_gfxEllapsedTimerId
            ,   APP_TIMER_MODE_REPEATED
            ,   gfxTimerCallback
        );
    APP_ERROR_CHECK( errorCode );

    errorCode = app_timer_start(
                m_gfxEllapsedTimerId
            ,   APP_TIMER_TICKS( LvglNotificationTime )
            ,   nullptr
        );
    APP_ERROR_CHECK( errorCode );
}

void
LvglGraphicsService::runTest()
{
    //lv_theme_t* pTheme = lv_theme_mono_init(0, NULL);
    lv_theme_t* pTheme = lv_theme_material_init(0, NULL);
    lv_theme_set_current(pTheme);

    lv_obj_t * scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/

    lv_obj_t * preload = lv_preload_create(lv_scr_act(), NULL);
    lv_preload_set_spin_time(preload, 10000);
    lv_obj_set_size(preload, 240, 240);
    lv_obj_align(preload, NULL, LV_ALIGN_CENTER, 0, 0);


     static lv_style_t styleMainLabel;
     lv_style_copy(&styleMainLabel, &lv_style_transp_tight);         /*Copy a built-in style as a starting point*/

     lv_obj_t* label1 = lv_label_create(scr, NULL);
    styleMainLabel.text.font = &lv_font_roboto_28;
    lv_label_set_style( label1 ,LV_LABEL_STYLE_MAIN, &styleMainLabel );
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_label_set_text(label1, "12:23");


// Line with clockwatch
    // static lv_point_t line_points[] = { {5, 5}, {70, 70}, {120, 10}, {180, 60}, {220, 10} };
    // static lv_style_t style_line;
    // lv_style_copy(&style_line, &lv_style_plain);
    // style_line.line.color = LV_COLOR_MAKE(0x00, 0x3b, 0x75);
    // style_line.line.width = 3;
    // style_line.line.rounded = 1;

    // /*Copy the previous line and apply the new style*/
    // lv_obj_t* line1;
    // line1 = lv_line_create(lv_scr_act(), NULL);
    // lv_line_set_points(line1, line_points, 5);     /*Set the points*/
    // lv_line_set_style(line1, LV_LINE_STYLE_MAIN, &style_line);
    // lv_obj_align(line1, NULL, LV_ALIGN_IN_TOP_MID, 0, 0);

    lv_obj_t* label2 = lv_label_create(scr, NULL);
    styleMainLabel.text.font = &lv_font_roboto_28;
    lv_label_set_style( label2 ,LV_LABEL_STYLE_MAIN, &styleMainLabel );

    lv_label_set_text(label2, "28/12/19");

    lv_obj_align(label2, NULL, LV_ALIGN_CENTER, 0, 30);

}

void
LvglGraphicsService::initLvglLogger()
{
    auto lvglLoggerCallback = cbc::obtain_connector(
        []( lv_log_level_t level, const char * file, long unsigned int line, const char * dsc )
        {
            switch( level )
            {
                case LV_LOG_LEVEL_ERROR:
                    Logger::Instance().logDebug( "[ERROR]:" );
                break;
                case LV_LOG_LEVEL_WARN:
                    Logger::Instance().logDebug( "[WARNING]:" );
                break;
                case LV_LOG_LEVEL_INFO:
                    Logger::Instance().logDebug( "[INFO]:" );
                break;
                case LV_LOG_LEVEL_TRACE:
                    Logger::Instance().logDebug( "[TRACE]:" );
                break;

                default:
                    Logger::Instance().logDebug( "[LVGL_LOG]:" );
            }
            Logger::Instance().logDebug( "File:"  );
            Logger::Instance().logDebug( file );
            Logger::Instance().logDebug( ":" );
            Logger::Instance().logDebugEndl( dsc );
        }
    );

    lv_log_register_print_cb( lvglLoggerCallback );
}

LvglGraphicsService::~LvglGraphicsService()
{

}

lv_disp_buf_t LvglGraphicsService::displayBuffer{};

LvglGraphicsService::TColorBuf
LvglGraphicsService::dispFrameBufFirst{};

LvglGraphicsService::TColorBuf
LvglGraphicsService::dispFrameBufSecond{};

std::unique_ptr<LvglGraphicsService>
createGraphicsService(std::unique_ptr<DisplayDriver::IDisplayDriver>&& _displayDriver)
{
    return std::make_unique<LvglGraphicsService>( std::move( _displayDriver ) );
}

};
