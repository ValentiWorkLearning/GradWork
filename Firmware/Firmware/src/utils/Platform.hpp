#pragma once
#include <cstdint>
#include <cstddef>

namespace Platform
{

#if defined (USE_DESKTOP_SIMULATOR)
    static constexpr size_t LogerImplSize = 1;
    static constexpr size_t LogerImplAlignment = 1;

    static constexpr size_t GraphicsBackendSize = 16;
    static constexpr size_t GraphicsBackendAlignment = 8;

    static constexpr size_t DateTimeImplSize = 224;
    static constexpr size_t DateTimeAlignment = 8;

    static constexpr size_t BatteryImplSize = 192;
    static constexpr size_t BatteryAlignment = 8;
#else
    static constexpr size_t LogerImplSize = 1;
    static constexpr size_t LogerImplAlignment = 1;

    static constexpr size_t SpiImplSize = 12;
    static constexpr size_t SpiImplAlignment = 4;

    static constexpr size_t GpioImplSize = 2;
    static constexpr size_t GpioImplAlignment = 2;

    static constexpr size_t GraphicsBackendSize = 8;
    static constexpr size_t GraphicsBackendAlignment = 4;

    static constexpr size_t DateTimeImplSize = 40;
    static constexpr size_t DateTimeAlignment = 4;

    static constexpr size_t BatteryImplSize = 48;
    static constexpr size_t BatteryAlignment = 8;
#endif
};