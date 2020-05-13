#pragma once

#include "lvgl.h"
#include "lv_conf.h"

#include "gs_platform_layer.hpp"

#include <array>
#include <memory>

#include "MetaUtils.hpp"

namespace Graphics::MainWindow
{
    class IGsMainWindow;
};

namespace Graphics
{

class LvglGraphicsService
{

public:

    explicit LvglGraphicsService(
            std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
        );

    ~LvglGraphicsService();

    void executeGlTask();

public:

    Graphics::MainWindow::IGsMainWindow& getMainWindow();

    Graphics::MainWindow::IGsMainWindow& getMainWindow() const;

private:

    static constexpr size_t DispHorRes = LV_HOR_RES_MAX*10;

    using TColorBuf = std::array<lv_color_t,DispHorRes>;

    static lv_disp_buf_t displayBuffer;
    static TColorBuf dispFrameBufFirst;

private:

    void initLvglLogger();

    void initDisplayDriver();

    void initMainWindow();

private:

    Meta::PointerWrapper<lv_disp_t,lv_disp_remove> m_glDisplay;

    std::unique_ptr<Graphics::PlatformBackend> m_pPlatformBackend;
    std::unique_ptr<Graphics::MainWindow::IGsMainWindow> m_pMainWindow;

    Meta::PointerWrapper<lv_task_t,lv_task_del> m_pMainWindowTick;
    Meta::PointerWrapper<lv_task_t, lv_task_del> m_pPageSwitch;
    Meta::PointerWrapper<lv_task_t, lv_task_del> m_pthemeChangeSwitch;

    lv_disp_drv_t m_glDisplayDriver;

};

std::unique_ptr<LvglGraphicsService> createGraphicsService(
        std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
    );

};
