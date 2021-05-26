#include "gs_platform_layer.hpp"
#include <logger/logger_service.hpp>

#include <lvgl.h>

#include <utils/CallbackConnector.hpp>
#include <utils/CoroUtils.hpp>

#include <ih/drivers/ih_display_idisplay.hpp>
#include <ih/drivers/ih_display_driver_creator.hpp>

#if defined USE_HARDWARE_DISPLAY_BACKEND || defined USE_HARDWARE_TEMPLATED_DISPLAY_BACKEND
#include <app_timer.h>
#include <nrf_drv_clock.h>

namespace
{
    APP_TIMER_DEF(m_gfxEllapsedTimerId);
}

namespace Graphics
{
#endif


#if defined (USE_HARDWARE_DISPLAY_BACKEND)

PlatformBackend::PlatformBackend()noexcept
    :   m_hardwareDisplayDriver{
            DisplayCreator::createDisplayDriver()
        }
{
}
#endif

#if defined (USE_HARDWARE_TEMPLATED_DISPLAY_BACKEND)
PlatformBackend::PlatformBackend()noexcept
    :   m_hardwareDisplayDriver{
        std::make_unique<TDisplayDriver>()
    }
{
};
#endif

#if defined USE_HARDWARE_DISPLAY_BACKEND || defined USE_HARDWARE_TEMPLATED_DISPLAY_BACKEND
void
PlatformBackend::platformDependentInit( lv_disp_drv_t* _displayDriver )noexcept
{
    getHardwareDisplayDriver()->initialize();

    auto hardwareDriverCallback = cbc::obtain_connector(
        [ this ]( lv_disp_drv_t* _displayDriver, const lv_area_t* _fillArea, lv_color_t* _colorFill )
        {
            getHardwareDisplayDriver()->fillRectangle(
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
            Simple::Lib::ExecuteLaterPool::Instance().processQueue();
        }
    );

    if(!_displayDriver)
        return;

    _displayDriver->flush_cb = hardwareDriverCallback;
    _displayDriver->wait_cb = waitCallback;

    getHardwareDisplayDriver()->onRectArreaFilled.connect(
        [this,_displayDriver]
        {
            lv_disp_flush_ready( _displayDriver );
        }
    );
}

void
PlatformBackend::initPlatformGfxTimer()noexcept
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
PlatformBackend::executeLvTaskHandler()noexcept
{
    if(!getHardwareDisplayDriver()->isInitialized())
        return;

    lv_task_handler();
}
} // namespace Graphics
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

PlatformBackend::PlatformBackend()noexcept = default;

void
PlatformBackend::platformDependentInit(lv_disp_drv_t* _displayDriver)noexcept
{
    monitor_init();
    _displayDriver->flush_cb = monitor_flush;
}

void
PlatformBackend::initPlatformGfxTimer()noexcept
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
PlatformBackend::indevPlatformInit()noexcept
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
PlatformBackend::memoryMonitor(lv_timer_t* _param)noexcept
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
PlatformBackend::executeLvTaskHandler()noexcept
{
    lv_task_handler();
    std::this_thread::sleep_for(
        std::chrono::milliseconds( LvglNotificationTime )
    );
}

}
#endif
