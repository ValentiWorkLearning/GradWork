#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/MetaUtils.hpp"
#include "utils/Platform.hpp"

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

    explicit LvglGraphicsService(
            std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
        );

    ~LvglGraphicsService();

    void executeGlTask();

public:

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow();

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow() const;

private:

    void initMainWindow();

private:

    static constexpr inline std::size_t kImplSize = Platform::GraphicsBackendSize;
    static constexpr inline std::size_t kImplAlignment = Platform::GraphicsBackendAlignment;

    class GSLvglServiceImpl;
    Utils::FastPimpl<GSLvglServiceImpl,Platform::GlLvglServiceImplSize,Platform::GlLvglServiceAlignment> m_pGraphicsServiceImpl;

};

std::unique_ptr<LvglGraphicsService> createGraphicsService();

};
