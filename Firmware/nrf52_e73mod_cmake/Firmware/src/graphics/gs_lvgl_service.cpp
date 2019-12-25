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
    // lv_obj_t * scr = lv_disp_get_scr_act(nullptr);

    // lv_theme_t* pTheme = lv_theme_material_init(0, NULL);
    // lv_theme_set_current(pTheme);

    // lv_obj_t* list = lv_list_create(scr, nullptr);
    // lv_obj_set_height(list, 2 * lv_obj_get_height(scr) / 3);
    // lv_obj_align(list, nullptr, LV_ALIGN_IN_TOP_MID, 0, LV_DPI / 4 + 5);

    // lv_obj_t* list_btn{nullptr};
    // list_btn = lv_list_add_btn(list, LV_SYMBOL_WIFI, "WiFi");

    // list_btn = lv_list_add_btn(list, LV_SYMBOL_GPS, "GPS");
    // list_btn = lv_list_add_btn(list, LV_SYMBOL_BLUETOOTH, "Bluetooth");
    // list_btn = lv_list_add_btn(list, LV_SYMBOL_AUDIO, "Sound");

     lv_obj_t * scr = lv_disp_get_scr_act(NULL);     /*Get the current screen*/

    /*Create a Label on the currently active screen*/
    lv_obj_t * label1 =  lv_label_create(scr, NULL);

    /*Modify the Label's text*/
    lv_label_set_text(label1, "21:39");

    /* Align the Label to the center
     * NULL means align on parent (which is the screen now)
     * 0, 0 at the end means an x, y offset after alignment*/
    lv_obj_align(label1, NULL, LV_ALIGN_CENTER, 0, 0);
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
