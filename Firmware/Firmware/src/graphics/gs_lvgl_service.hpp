#pragma once

#include "lvgl.h"
#include "lv_conf.h"

#include "platform/gs_platform_layer.hpp"

#include "utils/MetaUtils.hpp"

#include <array>
#include <memory>

namespace Graphics::MainWindow
{
    class IGsMainWindowModel;
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

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow();

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow() const;

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
    std::unique_ptr<Graphics::MainWindow::IGsMainWindowModel> m_pMainWindow;

    Meta::PointerWrapper<lv_task_t,lv_task_del> m_pMainWindowTick;
    Meta::PointerWrapper<lv_task_t, lv_task_del> m_pPageSwitch;
    Meta::PointerWrapper<lv_task_t, lv_task_del> m_pthemeChangeSwitch;

    lv_disp_drv_t m_glDisplayDriver;

};

std::unique_ptr<LvglGraphicsService> createGraphicsService(
        std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
    );

};
