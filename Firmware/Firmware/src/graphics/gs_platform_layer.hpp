#pragma once

#include <memory>
#include "lvgl.h"

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

    class PlatformBackendImpl;
    std::unique_ptr<PlatformBackendImpl> m_pBackendImpl;
};

std::unique_ptr<PlatformBackend> createPlatformBackend();

};