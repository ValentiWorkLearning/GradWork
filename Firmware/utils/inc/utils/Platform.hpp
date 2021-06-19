#pragma once
#include <cstddef>
#include <cstdint>

namespace Platform
{

#if defined(USE_DESKTOP_SIMULATOR)
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

static constexpr size_t GpioImplSize = 8;
static constexpr size_t GpioImplAlignment = 4;

static constexpr size_t GraphicsBackendSize = 4;
static constexpr size_t GraphicsBackendAlignment = 4;

static constexpr size_t GlLvglServiceImplSize = 60;
static constexpr size_t GlLvglServiceAlignment = 4;

static constexpr size_t DateTimeImplSize = 40;
static constexpr size_t DateTimeAlignment = 4;

static constexpr size_t BatteryImplSize = 48;
static constexpr size_t BatteryAlignment = 8;
#endif
}; // namespace Platform