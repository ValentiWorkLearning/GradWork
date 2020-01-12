#pragma once

#include "lvgl.h"
#include "lv_conf.h"

#include "gs_platform_layer.hpp"

#include <array>
#include <memory>

namespace Graphics
{

class LvglGraphicsService
{

public:

    LvglGraphicsService(
            std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
        );

    ~LvglGraphicsService();

    void runTest();

    void executeGlTask();

private:

    static constexpr size_t DispHorRes = LV_HOR_RES_MAX*10;

    using TColorBuf = std::array<lv_color_t,DispHorRes>;

    static lv_disp_buf_t displayBuffer;
    static TColorBuf dispFrameBufFirst;
    static TColorBuf dispFrameBufSecond;

private:

    void initLvglLogger();

private:

    lv_disp_t* m_glDisplay;
    std::unique_ptr<Graphics::PlatformBackend> m_pPlatformBackend;
    lv_disp_drv_t m_glDisplayDriver;
};

std::unique_ptr<LvglGraphicsService> createGraphicsService(
        std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
    );

};
