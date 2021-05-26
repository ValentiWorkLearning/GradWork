#pragma once

#include <memory>

#include <lvgl.h>

#ifdef USE_WINSDL_BACKEND
#include <thread>
#include <chrono>
#endif // USE_WINSDL_BACKEND


namespace DisplayDriver {
    class IDisplayDriver;
}

#if defined (USE_HARDWARE_TEMPLATED_DISPLAY_BACKEND)
    #include <display/display_coro_compact_gc9a01.hpp>
    #include <spi/spi_wrapper_async_templated.hpp>
    #include <backends/spi_backend_nrf.hpp>
#endif

#include <utils/FastPimpl.hpp>

namespace Graphics
{

class PlatformBackend
{

public:

    PlatformBackend()noexcept;

    void platformDependentInit( lv_disp_drv_t* _displayDriver )noexcept;

    void initPlatformGfxTimer()noexcept;

    void executeLvTaskHandler()noexcept;

private:

    static constexpr std::uint32_t LvglNotificationTime = 15;
#if defined USE_HARDWARE_DISPLAY_BACKEND
    using TDisplayDriver = std::unique_ptr<DisplayDriver::IDisplayDriver>;
#endif


#if defined USE_HARDWARE_TEMPLATED_DISPLAY_BACKEND
    using TSpiBus = Interface::SpiTemplated::SpiBus<
        Interface::SpiTemplated::NordicSpi<Interface::SpiTemplated::SpiInstance::M2>
    >;
    using TDisplayDriver =
         DisplayDriver::GC9A01Compact<TSpiBus, 240, 240>;
#endif

#if defined USE_HARDWARE_DISPLAY_BACKEND || USE_HARDWARE_TEMPLATED_DISPLAY_BACKEND
    auto getHardwareDisplayDriver()noexcept
    {
        return m_hardwareDisplayDriver.get();
    }
#endif
private:

    void indevPlatformInit()noexcept;

    void memoryMonitor(lv_timer_t* _param)noexcept;

private:

#if defined USE_HARDWARE_TEMPLATED_DISPLAY_BACKEND
    std::unique_ptr<TDisplayDriver> m_hardwareDisplayDriver;
#elif defined  USE_HARDWARE_DISPLAY_BACKEND
    TDisplayDriver m_hardwareDisplayDriver
#endif

#if defined USE_WINSDL_BACKEND
    std::thread m_tickThread;
    lv_indev_drv_t m_indevDriver;
#endif

};

} // namespace Graphics
