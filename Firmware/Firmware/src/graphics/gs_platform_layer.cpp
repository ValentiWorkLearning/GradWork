#include "gs_platform_layer.hpp"
#include "logger_service.hpp"

namespace
{
    static constexpr std::uint32_t LvglNotificationTime = 15;
    static constexpr std::uint32_t InitDelayTime = 100;
}

#include "CallbackConnector.hpp"

#if defined USE_ST7789V_BACKEND

#include "display/display_idisplay.hpp"
#include "display/display_st7789v.hpp"
#include "spi/spi_wrapper.hpp"

#include "nrf_delay.h"
#include "app_timer.h"
#include "nrf_drv_clock.h"

namespace
{
    APP_TIMER_DEF(m_gfxEllapsedTimerId);
}


namespace Graphics
{

class PlatformBackend::PlatformBackendImpl
{

public:

    PlatformBackendImpl()
        :   m_displaySpiInstance { Interface::Spi::createSpiBus<Interface::Spi::SpiInstance::M2>() }
        ,   m_hardwareDisplayDriver{
                DisplayDriver::createDisplayDriver(
                        m_displaySpiInstance.get()
                    ,   DisplayDriver::St7789v::Disp240_320::Width
                    ,   DisplayDriver::St7789v::Disp240_320::Height
                )
            }
    {
        nrf_delay_ms( InitDelayTime );
    }

    void platformDependentInit( lv_disp_drv_t* _displayDriver )
    {
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
        _displayDriver->flush_cb = hardwareDriverCallback;

        m_hardwareDisplayDriver->onRectArreaFilled.connect(
            [this,_displayDriver]
            {
                lv_disp_flush_ready( _displayDriver );
            }
        );
    }

    void initPlatformGfxTimer()
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

    void executeLvTaskHandler()
    {
        lv_task_handler();
    }

private:

    std::unique_ptr<DisplayDriver::IDisplayDriver> m_hardwareDisplayDriver;
    std::unique_ptr<Interface::Spi::SpiBus> m_displaySpiInstance;

};
}
#endif


#if defined USE_WINSDL_BACKEND

#include <thread>
#include <chrono>

#include "lvgl/lvgl.h"
#include "lv_drivers/display/monitor.h"
#include "lv_drivers/indev/mouse.h"
#include "lv_drivers/indev/keyboard.h"

#include <boost/format.hpp>

namespace Graphics
{

class PlatformBackend::PlatformBackendImpl
{
public:

    PlatformBackendImpl()
    {
        monitor_init();
    }

    void platformDependentInit(lv_disp_drv_t* _displayDriver)
    {
        _displayDriver->flush_cb = monitor_flush;
    }

    void initPlatformGfxTimer()
    {
        auto tickThread = std::thread(
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
        tickThread.detach();
        desktopPlatformInit();
    }

    void desktopPlatformInit()
    {
        lv_indev_drv_t indevDrv{};

        lv_indev_drv_init( &indevDrv );
        indevDrv.type = LV_INDEV_TYPE_POINTER;
        indevDrv.read_cb = mouse_read;
        lv_indev_drv_register( &indevDrv );

        auto memoryMonitorTask = cbc::obtain_connector(
            [this]( lv_task_t* _param )
            {
                memoryMonitor( _param );
            }
        );

        lv_task_create(
                memoryMonitorTask
            ,   3000
            ,   LV_TASK_PRIO_MID
            ,   nullptr
        );
    }

    void memoryMonitor(lv_task_t* _param)
    {
        boost::ignore_unused( _param );

        lv_mem_monitor_t moninor{};
        lv_mem_monitor( &moninor );

        Logger::Instance().logDebugEndl(
            boost::str(
                boost::format(
                    "Used: %1% , %2%%% fragmentation: %3%, biggest free: %4%"
                )   %   static_cast<std::uint32_t>( moninor.total_size - moninor.free_size )
                    %   static_cast<std::uint32_t>( moninor.used_pct )
                    %   static_cast<std::uint32_t>( moninor.frag_pct )
                    %   static_cast<std::uint32_t>( moninor.free_biggest_size )
            )
        );
    }

    void executeLvTaskHandler()
    {
        lv_task_handler();
        std::this_thread::sleep_for(
            std::chrono::milliseconds( LvglNotificationTime )
        );
    }

private:

};
}
#endif

namespace Graphics
{
PlatformBackend::PlatformBackend()
    :   m_pBackendImpl{
        std::make_unique<PlatformBackendImpl>()
    }
{
}

PlatformBackend::~PlatformBackend() = default;

void PlatformBackend::platformDependentInit( lv_disp_drv_t* _displayDriver )
{
    m_pBackendImpl->platformDependentInit( _displayDriver );
}

void PlatformBackend::initPlatformGfxTimer()
{
    m_pBackendImpl->initPlatformGfxTimer();
}

void PlatformBackend::executeTask()
{
    m_pBackendImpl->executeLvTaskHandler();
}

std::unique_ptr<PlatformBackend>
createPlatformBackend()
{
    return std::make_unique<PlatformBackend>();
}

}
