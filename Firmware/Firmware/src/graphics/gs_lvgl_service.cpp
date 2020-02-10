#include "gs_lvgl_service.hpp"

#include "lvgl.h"

#include "gs_main_window.hpp"
#include "gs_event_dispatcher.hpp"

#include "widgets_layer/lvgl_ui.hpp"

#include "widgets_layer/ih/gs_ievent_handler.hpp"

#include "widgets_layer/widgets/battery/gs_battery_handler.hpp"
#include "widgets_layer/widgets/battery/gs_battery_widget.hpp"


#include "CallbackConnector.hpp"
#include "logger_service.hpp"


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
LvglGraphicsService::runTest()
{
    //LvglUi::createWidgetsDemo();
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

    m_glDisplay = lv_disp_drv_register( &m_glDisplayDriver );

    m_pPlatformBackend->initPlatformGfxTimer();
}

void
LvglGraphicsService::initMainWindow()
{
    m_pMainWindow = Graphics::MainWindow::createMainWindow();
    // TODO create the lvlg task for ellaped event processing


    m_pBatteryWidget = Widgets::createBatteryWidget();
    m_pBatteryWidgetController = std::move( Widgets::createBatteryWidgetHandler( m_pBatteryWidget ) );

    m_pMainWindow->getEventDispatcher().subscribe(
            Events::EventGroup::Battery
        ,   [ this]( const Events::TEvent& _event )
        {
            m_pBatteryWidgetController->handleEvent( _event );
        }
    );

    auto mainWindowTimer = cbc::obtain_connector(
        [this](lv_task_t* _pTask)
        {
            m_pMainWindow->handleEventTimerEllapsed();
        }
    );

    m_pMainWindowTick = lv_task_create(
            mainWindowTimer
        ,   50
        ,   LV_TASK_PRIO_MID
        ,   nullptr
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
