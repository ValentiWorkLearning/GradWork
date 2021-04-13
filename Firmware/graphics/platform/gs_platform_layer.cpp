#include "gs_platform_layer.hpp"
#include <logger/logger_service.hpp>

#include <lvgl.h>

#include <utils/CallbackConnector.hpp>
#include <utils/CoroUtils.hpp>

#if defined USE_HARDWARE_DISPLAY_BACKEND

#include <ih/drivers/ih_display_idisplay.hpp>
#include <ih/drivers/ih_display_driver_creator.hpp>

#include <app_timer.h>
#include <nrf_drv_clock.h>

namespace
{
    APP_TIMER_DEF(m_gfxEllapsedTimerId);
}

namespace Graphics
{

PlatformBackend::PlatformBackend()
    :   m_hardwareDisplayDriver{
            DisplayCreator::createDisplayDriver()
        }
{
}

void
PlatformBackend::platformDependentInit( lv_disp_drv_t* _displayDriver )
{
    m_hardwareDisplayDriver->initialize();

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

    auto waitCallback = cbc::obtain_connector(
        [](lv_disp_drv_t * disp_drv)
        {
            CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
        }
    );

    _displayDriver->flush_cb = hardwareDriverCallback;
    _displayDriver->wait_cb = waitCallback;

    m_hardwareDisplayDriver->onRectArreaFilled.connect(
        [this,_displayDriver]
        {
            LOG_DEBUG_ENDL("lv_disp_flush_ready CALLED");
            lv_disp_flush_ready( _displayDriver );
        }
    );
}

void
PlatformBackend::initPlatformGfxTimer()
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
PlatformBackend::executeLvTaskHandler()
{
    if(!m_hardwareDisplayDriver->isInitialized())
        return;

    lv_task_handler();
}
}
#endif


#if defined USE_WINSDL_BACKEND

#include <thread>
#include <chrono>

#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"

#include <fmt/format.h>

namespace Graphics
{

PlatformBackend::PlatformBackend() = default;

void
PlatformBackend::platformDependentInit(lv_disp_drv_t* _displayDriver)
{
    monitor_init();
    _displayDriver->flush_cb = monitor_flush;
}

void
PlatformBackend::initPlatformGfxTimer()
{
    m_tickThread = std::thread(
        []
        {
            while (true)
            {
                lv_tick_inc( LvglNotificationTime );
                std::this_thread::sleep_for(
                    std::chrono::milliseconds( LvglNotificationTime )
                );
            }

        }
    );
    m_tickThread.detach();
    indevPlatformInit();
    lv_indev_drv_init(&m_indevDriver);
}

void
PlatformBackend::indevPlatformInit()
{
    
    m_indevDriver.type = LV_INDEV_TYPE_POINTER;
    m_indevDriver.read_cb = mouse_read;
    lv_indev_drv_register( &m_indevDriver );

    auto memoryMonitorTask = cbc::obtain_connector(
        [this]( lv_timer_t* _param )
        {
            memoryMonitor( _param );
        }
    );

    lv_timer_create(
            memoryMonitorTask
        ,   10
        ,   nullptr
    );
}

void
PlatformBackend::memoryMonitor(lv_timer_t* _param)
{
    static_cast<void>( _param );

    lv_mem_monitor_t moninor{};
    lv_mem_monitor( &moninor );

    LOG_DEBUG_ENDL(
            fmt::format(
                "Used: {} , {}% fragmentation: {}, biggest free: {}"
             ,   static_cast<std::uint32_t>( moninor.total_size - moninor.free_size )
             ,   static_cast<std::uint32_t>( moninor.used_pct )
             ,   static_cast<std::uint32_t>( moninor.frag_pct )
             ,   static_cast<std::uint32_t>( moninor.free_biggest_size )
            )
        );
}

void
PlatformBackend::executeLvTaskHandler()
{
    lv_task_handler();
    std::this_thread::sleep_for(
        std::chrono::milliseconds( LvglNotificationTime )
    );
}

}
#endif
