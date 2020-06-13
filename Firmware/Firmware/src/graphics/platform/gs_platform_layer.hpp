#pragma once

#include <memory>
#include "lvgl.h"

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

namespace Graphics
{

class PlatformBackend
{

public:

    explicit PlatformBackend();

    void platformDependentInit( lv_disp_drv_t* _displayDriver );

    void executeTask();

    void initPlatformGfxTimer();

    ~PlatformBackend();

private:

    static constexpr inline std::size_t kImplSize = Platform::GraphicsBackendSize;
    static constexpr inline std::size_t kImplAlignment = Platform::GraphicsBackendAlignment;

    class PlatformBackendImpl;
    Utils::FastPimpl<PlatformBackendImpl,kImplSize,kImplAlignment> m_pBackendImpl;
};

std::unique_ptr<PlatformBackend> createPlatformBackend();

};