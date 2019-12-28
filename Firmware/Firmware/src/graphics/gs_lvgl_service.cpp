#include "gs_lvgl_service.hpp"

#include "lvgl.h"

#include "CallbackConnector.hpp"
#include "logger_service.hpp"

#include "nrf_delay.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"

#include "widgets_layer/lvgl_ui.hpp"

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
    LvglUi::createWidgetsDemo();
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
