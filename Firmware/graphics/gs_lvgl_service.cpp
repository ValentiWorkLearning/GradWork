#include "gs_lvgl_service.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_itheme_controller.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"
#include "ih/pages/gs_ihealth_page_view.hpp"
#include "ih/pages/gs_iplayer_page_view.hpp"

#include "widgets_layer/gs_main_window.hpp"
#include "widgets_layer/gs_main_window_view.hpp"

#include "widgets_layer/lvgl_views_creators/gs_widgets_creator.hpp"
#include "widgets_layer/lvgl_views_creators/gs_pages_creator.hpp"

#include "gs_event_dispatcher.hpp"


#include "platform/gs_platform_layer.hpp"

#include "lvgl.h"
#include "lv_conf.h"

#include "utils/CallbackConnector.hpp"
#include "logger/logger_service.hpp"

#include <array>
#include <memory>

namespace Graphics
{

LvglGraphicsService::LvglGraphicsService(
        )   :   m_pGraphicsServiceImpl{ std::make_unique<GSLvglServiceImpl>() }
{
}

class LvglGraphicsService::GSLvglServiceImpl
{

public:

    GSLvglServiceImpl(
    )   :   m_glDisplay{ nullptr }
        ,   m_pMainWindowTick{ nullptr }
        ,   m_pPageSwitch{ nullptr }
        ,   m_pthemeChangeSwitch{ nullptr }
        ,   m_glDisplayDriver{}
        ,   m_pPlatformBackend{}
    {
        initLvglLogger();
        initDisplayDriver();
        initMainWindow();
    }

public:

    void executeGlTask()
    {
        m_pPlatformBackend.executeLvTaskHandler();
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
                        LOG_DEBUG( "[ERROR]:" );
                    break;
                    case LV_LOG_LEVEL_WARN:
                        LOG_DEBUG( "[WARNING]:" );
                    break;
                    case LV_LOG_LEVEL_INFO:
                        LOG_DEBUG( "[INFO]:" );
                    break;
                    case LV_LOG_LEVEL_TRACE:
                        LOG_DEBUG( "[TRACE]:" );
                    break;

                    default:
                        LOG_DEBUG( "[LVGL_LOG]:" );
                }
                LOG_DEBUG( "File:"  );
                LOG_DEBUG( file );
                LOG_DEBUG( ":" );
                LOG_DEBUG(":functon");
                LOG_DEBUG(functionName);
                LOG_DEBUG_ENDL( dsc );
            }
        );

        lv_log_register_print_cb( lvglLoggerCallback );
    }

    void initDisplayDriver()
    {
        lv_init();

        lv_disp_draw_buf_init(
                        &displayBuffer
                    ,   &dispFrameBufFirst
                    ,   nullptr
                    ,   DispHorRes
                );

        lv_disp_drv_init( &m_glDisplayDriver );
        m_glDisplayDriver.draw_buf = &displayBuffer;

        // auto monitorCallback = cbc::obtain_connector(
        //     []( lv_disp_drv_t * disp_drv, uint32_t time, uint32_t px )
        //     {
        //         LOG_DEBUG("Refresh time:");
        //         LOG_DEBUG_ENDL( time );
        //         LOG_DEBUG("Refreshed pixels:");
        //         LOG_DEBUG_ENDL( px );
        //     }
        // );

        //m_glDisplayDriver.monitor_cb = monitorCallback;
        m_pPlatformBackend.platformDependentInit( &m_glDisplayDriver );

        m_glDisplay.reset( lv_disp_drv_register( &m_glDisplayDriver ) );

        m_pPlatformBackend.initPlatformGfxTimer();
    }

    void initMainWindow()
    {
        auto pMainWindowView = Graphics::MainWindow::createMainWindowView();
        auto pWidgetsCreator = Graphics::Widgets::createLvglWidgetsCreator();
        auto pPagesCreator = Graphics::Views::createLvglPagesCreator();

        m_pMainWindow = Graphics::MainWindow::createMainWindow(
                std::move( pMainWindowView )
            ,   std::move( pWidgetsCreator )
            ,   std::move( pPagesCreator )
        );
        // TODO create the lvlg task for ellaped event processing

        auto mainWindowTimer = cbc::obtain_connector(
            [this](lv_timer_t* _pTask)
            {
                m_pMainWindow->handleEventTimerEllapsed();
            }
        );

        m_pMainWindowTick.reset( lv_timer_create(
                    mainWindowTimer
                ,   50
                ,   nullptr
            )
        );

        m_pMainWindow->setPageActive(
            Views::IClockWatchPage::ClockPageName
        );

        auto pageToggle = cbc::obtain_connector(
            [this](lv_timer_t* _pTask)
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
            [this](lv_timer_t* _pTask)
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

        // m_pPageSwitch.reset(
        //     lv_task_create(
        //             pageToggle
        //         ,   4100
        //         ,   LV_TASK_PRIO_MID
        //         ,   nullptr
        //     )
        // );

        m_pthemeChangeSwitch.reset(
            lv_timer_create(
                    themeChange
                ,   2000
                ,   nullptr
            )
        );
    }

private:

    static constexpr size_t DispHorRes = LV_HOR_RES_MAX*10;

    using TColorBuf = std::array<lv_color_t,DispHorRes>;

    static lv_disp_draw_buf_t displayBuffer;
    static TColorBuf dispFrameBufFirst;

private:

    Meta::PointerWrapper<lv_disp_t,lv_disp_remove> m_glDisplay;
    Meta::PointerWrapper<lv_timer_t, lv_timer_del> m_pMainWindowTick;
    Meta::PointerWrapper<lv_timer_t, lv_timer_del> m_pPageSwitch;
    Meta::PointerWrapper<lv_timer_t, lv_timer_del> m_pthemeChangeSwitch;

    lv_disp_drv_t m_glDisplayDriver;

    Graphics::PlatformBackend m_pPlatformBackend;
    std::unique_ptr<Graphics::MainWindow::IGsMainWindowModel> m_pMainWindow;
};

lv_disp_draw_buf_t LvglGraphicsService::GSLvglServiceImpl::displayBuffer{};

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
    return std::make_unique<LvglGraphicsService>();
}

};
