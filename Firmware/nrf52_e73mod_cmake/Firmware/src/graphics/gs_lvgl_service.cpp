#include "gs_lvgl_service.hpp"

#include "lvgl.h"

#include "CallbackConnector.hpp"
#include "logger_service.hpp"
#include "nrf_delay.h"

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
            m_hardwareDisplayDriver->onRectArreaFilled.connect(
                [this,_displayDriver]
                {
                    lv_disp_flush_ready( _displayDriver );
                    lv_log_add( LV_LOG_LEVEL_TRACE, __FILE__, __LINE__, "display flush ready" );
                }
            );
      }
    );

    m_glDisplayDriver.flush_cb = hardwareDriverCallback;

    m_glDisplay = lv_disp_drv_register( &m_glDisplayDriver );
}

#define BUF_W 20
#define BUF_H 100


static lv_color_t buf[BUF_W * BUF_H];
void
LvglGraphicsService::runTest()
{

lv_color_t * buf_p = buf;
for(uint16_t y = 0; y < BUF_H; y++) {
    lv_color_t c = lv_color_mix(LV_COLOR_RED, LV_COLOR_PURPLE, (y * 255) / BUF_H);
    for(uint16_t x = 0; x < BUF_W; x++){
        (*buf_p) =  c;
        buf_p++;
    }
}

lv_area_t a;
a.x1 = 50;
a.y1 = 40;
a.x2 = a.x1 + BUF_W - 1;
a.y2 = a.y1 + BUF_H - 1;

m_glDisplayDriver.flush_cb(nullptr, &a, buf);

nrf_delay_ms( 15 );

a.x1 = 70;
a.y1 = 60;
a.x2 = a.x1 + BUF_W - 1;
a.y2 = a.y1 + BUF_H - 1;

m_glDisplayDriver.flush_cb(nullptr, &a, buf);

nrf_delay_ms( 15 );

a.x1 = 90;
a.y1 = 80;
a.x2 = a.x1 + BUF_W - 1;
a.y2 = a.y1 + BUF_H - 1;

m_glDisplayDriver.flush_cb(nullptr, &a, buf);

nrf_delay_ms( 15 );
a.x1 = 110;
a.y1 = 100;
a.x2 = a.x1 + BUF_W - 1;
a.y2 = a.y1 + BUF_H - 1;

m_glDisplayDriver.flush_cb(nullptr, &a, buf);

nrf_delay_ms( 15 );
a.x1 = 130;
a.y1 = 80;
a.x2 = a.x1 + BUF_W - 1;
a.y2 = a.y1 + BUF_H - 1;

m_glDisplayDriver.flush_cb(nullptr, &a, buf);

nrf_delay_ms( 15 );
a.x1 = 150;
a.y1 = 60;
a.x2 = a.x1 + BUF_W - 1;
a.y2 = a.y1 + BUF_H - 1;

m_glDisplayDriver.flush_cb(nullptr, &a, buf);

nrf_delay_ms( 15 );
a.x1 = 170;
a.y1 = 40;
a.x2 = a.x1 + BUF_W - 1;
a.y2 = a.y1 + BUF_H - 1;

m_glDisplayDriver.flush_cb(nullptr, &a, buf);

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
