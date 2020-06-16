#include "gs_lvgl_service.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_itheme_controller.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"
#include "ih/pages/gs_ihealth_page_view.hpp"
#include "ih/pages/gs_iplayer_page_view.hpp"

#include "widgets_layer/gs_main_window.hpp"
#include "widgets_layer/gs_main_window_view.hpp"

#include "gs_event_dispatcher.hpp"

#include "utils/CallbackConnector.hpp"
#include "logger/logger_service.hpp"

#include "platform/gs_platform_layer.hpp"

#include "lvgl.h"
#include "lv_conf.h"

#include <array>
#include <memory>

namespace Graphics
{

LvglGraphicsService::LvglGraphicsService(
            std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
        )   :   m_pGraphicsServiceImpl{ std::make_unique<GSLvglServiceImpl>(std::move( _platformBackend ) )}
{
}

class LvglGraphicsService::GSLvglServiceImpl
{

public:

    GSLvglServiceImpl(
        std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
    )   :   m_glDisplay{ nullptr }
        ,   m_pMainWindowTick{ nullptr }
        ,   m_pPageSwitch{ nullptr }
        ,   m_pthemeChangeSwitch{ nullptr }
        ,   m_glDisplayDriver{}
        ,   m_pPlatformBackend{ std::move( _platformBackend ) }
    {
        initLvglLogger();
        initDisplayDriver();
        initMainWindow();
    }

public:

    void executeGlTask()
    {
        m_pPlatformBackend->executeTask();
    }

public:

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow()
    {
        return *m_pMainWindow;
    }

    Graphics::MainWindow::IGsMainWindowModel& getMainWindow() const
    {
        return *m_pMainWindow;
    }

private:

    void initLvglLogger()
    {
        auto lvglLoggerCallback = cbc::obtain_connector(
            []( lv_log_level_t level, const char * file, std::uint32_t line, const char * functionName, const char* dsc)
            {
                switch( level )
                {
                    case LV_LOG_LEVEL_ERROR:
                        Logger::Instance().logDebug( "[ERROR]:" );
                    break;
                    case LV_LOG_LEVEL_WARN:
                        Logger::Instance().logDebug( "[WARNING]:" );
                    break;
                    case LV_LOG_LEVEL_INFO:
                        Logger::Instance().logDebug( "[INFO]:" );
                    break;
                    case LV_LOG_LEVEL_TRACE:
                        Logger::Instance().logDebug( "[TRACE]:" );
                    break;

                    default:
                        Logger::Instance().logDebug( "[LVGL_LOG]:" );
                }
                Logger::Instance().logDebug( "File:"  );
                Logger::Instance().logDebug( file );
                Logger::Instance().logDebug( ":" );
                Logger::Instance().logDebug(":functon");
                Logger::Instance().logDebug(functionName);
                Logger::Instance().logDebugEndl( dsc );
            }
        );

        lv_log_register_print_cb( lvglLoggerCallback );
    }

    void initDisplayDriver()
    {
        lv_init();

        lv_disp_buf_init(
                        &displayBuffer
                    ,   &dispFrameBufFirst
                    ,   nullptr
                    ,   DispHorRes
                );

        lv_disp_drv_init( &m_glDisplayDriver );
        m_glDisplayDriver.buffer = &displayBuffer;

        // auto monitorCallback = cbc::obtain_connector(
        //     []( lv_disp_drv_t * disp_drv, uint32_t time, uint32_t px )
        //     {
        //         Logger::Instance().logDebug("Refresh time:");
        //         Logger::Instance().logDebugEndl( time );
        //         Logger::Instance().logDebug("Refreshed pixels:");
        //         Logger::Instance().logDebugEndl( px );
        //     }
        // );

        //m_glDisplayDriver.monitor_cb = monitorCallback;
        m_pPlatformBackend->platformDependentInit( &m_glDisplayDriver );

        m_glDisplay.reset( lv_disp_drv_register( &m_glDisplayDriver ) );

        m_pPlatformBackend->initPlatformGfxTimer();
    }

    void initMainWindow()
    {
        auto pMainWindowView = Graphics::MainWindow::createMainWindowView();
        m_pMainWindow = Graphics::MainWindow::createMainWindow( std::move( pMainWindowView ) );
        // TODO create the lvlg task for ellaped event processing

        auto mainWindowTimer = cbc::obtain_connector(
            [this](lv_task_t* _pTask)
            {
                m_pMainWindow->handleEventTimerEllapsed();
            }
        );

        m_pMainWindowTick.reset( lv_task_create(
                    mainWindowTimer
                ,   50
                ,   LV_TASK_PRIO_MID
                ,   nullptr
            )
        );

        m_pMainWindow->setPageActive(
            Views::IClockWatchPage::ClockPageName
        );

        auto pageToggle = cbc::obtain_connector(
            [this](lv_task_t* _pTask)
            {
                static std::uint8_t toggle{ 0 };
                std::string_view pageToSet{};

                switch (toggle)
                {
                case 0:
                    pageToSet = Views::IHealthWatchPage::HealthPageName;
                    ++toggle;
                    break;
                case 1:
                    pageToSet = Views::IPlayerWatchPage::PlayerPageName;
                    ++toggle;
                    break;
                case 2:
                    pageToSet = Views::IClockWatchPage::ClockPageName;
                    ++toggle;
                    break;
                case 3:
                    toggle = 0;
                    pageToSet = Views::IClockWatchPage::ClockPageName;
                    break;
                default:
                    toggle = 0;
                    pageToSet = Views::IClockWatchPage::ClockPageName;
                    break;
                }
                m_pMainWindow->setPageActive(
                    pageToSet
                );
            }
        );

        auto themeChange = cbc::obtain_connector(
            [this](lv_task_t* _pTask)
            {
                auto themeController = getMainWindow().getThemeController();
                auto activeTheme = themeController->getActiveTheme();
                if (activeTheme == Theme::ColorTheme::Night)
                {
                    themeController->setActiveTheme( Theme::ColorTheme::Pastele );
                }
                else {
                    themeController->setActiveTheme(Theme::ColorTheme::Night);
                }

            }
        );

        m_pPageSwitch.reset(
            lv_task_create(
                    pageToggle
                ,   4100
                ,   LV_TASK_PRIO_MID
                ,   nullptr
            )
        );

        m_pthemeChangeSwitch.reset(
            lv_task_create(
                    themeChange
                ,   2000
                ,   LV_TASK_PRIO_MID
                ,   nullptr
            )
        );
    }

private:

    static constexpr size_t DispHorRes = LV_HOR_RES_MAX*10;

    using TColorBuf = std::array<lv_color_t,DispHorRes>;

    static lv_disp_buf_t displayBuffer;
    static TColorBuf dispFrameBufFirst;

private:

    Meta::PointerWrapper<lv_disp_t,lv_disp_remove> m_glDisplay;
    Meta::PointerWrapper<lv_task_t,lv_task_del> m_pMainWindowTick;
    Meta::PointerWrapper<lv_task_t, lv_task_del> m_pPageSwitch;
    Meta::PointerWrapper<lv_task_t, lv_task_del> m_pthemeChangeSwitch;

    lv_disp_drv_t m_glDisplayDriver;

    std::unique_ptr<Graphics::PlatformBackend> m_pPlatformBackend;
    std::unique_ptr<Graphics::MainWindow::IGsMainWindowModel> m_pMainWindow;
};

lv_disp_buf_t LvglGraphicsService::GSLvglServiceImpl::displayBuffer{};

LvglGraphicsService::GSLvglServiceImpl::TColorBuf
LvglGraphicsService::GSLvglServiceImpl::dispFrameBufFirst{};

LvglGraphicsService::~LvglGraphicsService() = default;


void LvglGraphicsService::executeGlTask()
{
    m_pGraphicsServiceImpl->executeGlTask();
}

Graphics::MainWindow::IGsMainWindowModel&
LvglGraphicsService::getMainWindow()
{
    return m_pGraphicsServiceImpl->getMainWindow();
}

Graphics::MainWindow::IGsMainWindowModel&
LvglGraphicsService::getMainWindow() const
{
    return m_pGraphicsServiceImpl->getMainWindow();
}

std::unique_ptr<LvglGraphicsService>
createGraphicsService()
{
    return std::make_unique<LvglGraphicsService>(
        Graphics::createPlatformBackend()
    );
}

};
