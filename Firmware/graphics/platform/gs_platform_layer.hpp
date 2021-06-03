#pragma once

#include <memory>

#include <lvgl.h>

#ifdef USE_WINSDL_BACKEND
#include <chrono>
#include <thread>
#endif // USE_WINSDL_BACKEND

namespace DisplayDriver
{
class IDisplayDriver;
}

#if defined(USE_HARDWARE_DISPLAY_BACKEND)
#include <backends/spi_backend_nrf.hpp>
#include <display/display_coro_compact_gc9a01.hpp>
#include <spi/spi_wrapper_async_templated.hpp>

using TSpiBus = Interface::SpiTemplated::SpiBus<
    Interface::SpiTemplated::NordicSpi<Interface::SpiTemplated::SpiInstance::M2>>;
using TDisplayDriver = DisplayDriver::GC9A01Compact<TSpiBus, 240, 240>;
#endif

namespace Graphics
{

class PlatformBackend
{

public:
    PlatformBackend() noexcept;

    void platformDependentInit(lv_disp_drv_t* _displayDriver) noexcept;

    void initPlatformGfxTimer() noexcept;

    void executeLvTaskHandler() noexcept;

private:
    static constexpr std::uint32_t LvglNotificationTime = 15;

private:
    void indevPlatformInit() noexcept;

    void memoryMonitor(lv_timer_t* _param) noexcept;

private:
#if defined (USE_HARDWARE_DISPLAY_BACKEND)
    std::unique_ptr<TDisplayDriver> m_hardwareDisplayDriver;
#endif

#if defined USE_WINSDL_BACKEND
    std::thread m_tickThread;
    lv_indev_drv_t m_indevDriver;
#endif
};

} // namespace Graphics
