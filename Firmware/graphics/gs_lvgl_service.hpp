#pragma once

#include "utils/MetaUtils.hpp"
#include <memory>

namespace Graphics
{
    class PlatformBackend;
};

namespace Graphics::MainWindow
{
    class IGsMainWindowModel;
};

namespace Graphics
{

class LvglGraphicsService
{

public:

    explicit LvglGraphicsService()noexcept;

    ~LvglGraphicsService()noexcept;

    void executeGlTask()noexcept;

public:

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow()noexcept;

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow() const noexcept;

private:

    void initMainWindow() noexcept;

private:

    class GSLvglServiceImpl;
    std::unique_ptr<GSLvglServiceImpl> m_pGraphicsServiceImpl;

};

std::unique_ptr<LvglGraphicsService> createGraphicsService();

};
