#include "gs_lvgl_service.hpp"

#include "lvgl.h"

#include "gs_main_window.hpp"
#include "gs_event_dispatcher.hpp"

#include "CallbackConnector.hpp"
#include "logger_service.hpp"

#include "ih/gs_itheme_controller.hpp"

#include "widgets_layer/pages/clock_page/gs_iclock_page_view.hpp"
#include "widgets_layer/pages/health_page/gs_ihealth_page_view.hpp"
#include "widgets_layer/pages/player_page/gs_iplayer_page_view.hpp"

#include "gs_events.hpp"

namespace Graphics
{

LvglGraphicsService::LvglGraphicsService(
            std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend
        )   :   m_pPlatformBackend{ std::move( _platformBackend ) }
            ,   m_pMainWindowTick{nullptr}
{
    initLvglLogger();
    initDisplayDriver();
    initMainWindow();
}

void LvglGraphicsService::executeGlTask()
{
    m_pPlatformBackend->executeTask();
}

void
LvglGraphicsService::initLvglLogger()
{

    auto lvglLoggerCallback = cbc::obtain_connector(
        []( lv_log_level_t level, const char * file, std::uint32_t line, const char * dsc )
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
            Logger::Instance().logDebugEndl( dsc );
        }
    );

    lv_log_register_print_cb( lvglLoggerCallback );
}

void
LvglGraphicsService::initDisplayDriver()
{
    lv_init();

    lv_disp_buf_init(
                    &displayBuffer
                ,   &dispFrameBufFirst
                ,   &dispFrameBufSecond
                ,   DispHorRes
            );

    lv_disp_drv_init( &m_glDisplayDriver );
    m_glDisplayDriver.buffer = &displayBuffer;

    auto monitorCallback = cbc::obtain_connector(
        []( lv_disp_drv_t * disp_drv, uint32_t time, uint32_t px )
        {
            std::array<char, 10> str{};
            if( auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(),time); ec == std::errc() )
            {
                Logger::Instance().logDebug("Refresh time:");
                Logger::Instance().logDebugEndl( std::string_view( str.data(), p - str.data() ) );
            }

            if( auto [p, ec] = std::to_chars(str.data(), str.data() + str.size(),px ); ec == std::errc() )
            {
                Logger::Instance().logDebug("Refreshed pixels:");
                Logger::Instance().logDebugEndl( std::string_view( str.data(), p - str.data() ) );
            }
        }
    );

    m_glDisplayDriver.monitor_cb = monitorCallback;
    m_pPlatformBackend->platformDependentInit( &m_glDisplayDriver );

    m_glDisplay.reset( lv_disp_drv_register( &m_glDisplayDriver ) );

    m_pPlatformBackend->initPlatformGfxTimer();
}

void
LvglGraphicsService::initMainWindow()
{
    m_pMainWindow = Graphics::MainWindow::createMainWindow();
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

Graphics::MainWindow::IGsMainWindow&
LvglGraphicsService::getMainWindow()
{
    return *m_pMainWindow;
}

Graphics::MainWindow::IGsMainWindow&
LvglGraphicsService::getMainWindow() const
{
    return *m_pMainWindow;
}

LvglGraphicsService::~LvglGraphicsService() = default;

lv_disp_buf_t LvglGraphicsService::displayBuffer{};

LvglGraphicsService::TColorBuf
LvglGraphicsService::dispFrameBufFirst{};

LvglGraphicsService::TColorBuf
LvglGraphicsService::dispFrameBufSecond{};

std::unique_ptr<LvglGraphicsService>
createGraphicsService(
    std::unique_ptr<Graphics::PlatformBackend>&& _platformBackend)
{
    return std::make_unique<LvglGraphicsService>( std::move( _platformBackend ) );
}

};
