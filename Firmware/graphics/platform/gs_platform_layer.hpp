#pragma once

#include <memory>

#include "lvgl.h"

#ifdef USE_WINSDL_BACKEND
#include <thread>
#include <chrono>
#endif // USE_WINSDL_BACKEND


namespace DisplayDriver {
    class IDisplayDriver;
}

namespace Graphics
{

class PlatformBackend
{

public:

    PlatformBackend();

    void platformDependentInit( lv_disp_drv_t* _displayDriver );

    void initPlatformGfxTimer();

    void executeLvTaskHandler();

private:

    static constexpr std::uint32_t LvglNotificationTime = 15;

private:

    void indevPlatformInit();

    void memoryMonitor(lv_timer_t* _param);

private:

#if defined USE_HARDWARE_DISPLAY_BACKEND
    std::unique_ptr<DisplayDriver::IDisplayDriver> m_hardwareDisplayDriver;
#elif defined USE_WINSDL_BACKEND
    std::thread m_tickThread;
    lv_indev_drv_t m_indevDriver;
#endif

};

} // namespace Graphics
