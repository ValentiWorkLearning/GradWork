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

    explicit LvglGraphicsService();

    ~LvglGraphicsService();

    void executeGlTask();

public:

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow();

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow() const;

private:

    void initMainWindow();

private:

    class GSLvglServiceImpl;
    std::unique_ptr<GSLvglServiceImpl> m_pGraphicsServiceImpl;

};

std::unique_ptr<LvglGraphicsService> createGraphicsService();

};
