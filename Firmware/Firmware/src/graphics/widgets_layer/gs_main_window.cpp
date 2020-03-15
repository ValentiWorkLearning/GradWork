#include "gs_main_window.hpp"
#include "gs_page_view_object.hpp"

#include "gs_events.hpp"
#include "gs_event_dispatcher.hpp"

#include "gs_theme_controller.hpp"

#include "gs_ipage_view_object.hpp"

#include "ih/gs_ievent_handler.hpp"

#include "widgets/battery/gs_battery_handler.hpp"
#include "widgets/battery/gs_battery_widget.hpp"

#include "widgets/pages_switch/gs_pages_switch.hpp"
#include "widgets/bluetooth/gs_bluetooth_widget.hpp"

#include "pages/clock_page/gs_clock_page_view.hpp"
#include "pages/clock_page/gs_clock_page_handler.hpp"

#include "pages/health_page/gs_health_page_view.hpp"

#include "pages/player_page/gs_player_page_view.hpp"

#include "lvgl_ui.hpp"

namespace Graphics::MainWindow
{

GsMainWindow::GsMainWindow()
    :
        m_currentPageName{}
    ,   m_pEventsDispatcher{ std::move( Events::createEventDispatcher() ) }
    ,   m_pThemeController{ std::move( Theme::createThemeController(
                    Theme::ColorTheme::Pastele
                ,   Width
                ,   Height
                )
            )
        }
{
    initBackground();
    initWatchPage();
    initHealthPage();
    initPlayerPage();
}

GsMainWindow::~GsMainWindow() = default;

void GsMainWindow::addPage(
        std::shared_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    )
{
    auto localShared { std::move( _toAdd ) };
    auto pageName{ localShared->getPageName() };
    m_pagesStorage.insert( {pageName,localShared } );

    localShared->hide();
}

void GsMainWindow::setPageActive( std::string_view _pageName )
{
    if( !m_currentPageName.empty() )
        m_pagesStorage.at( m_currentPageName )->hide();

    m_currentPageName = _pageName;
    m_pagesStorage.at( m_currentPageName )->show();

    onActivePageChanged.emit( m_currentPageName );
}

std::shared_ptr<Graphics::Views::IPageViewObject>
GsMainWindow::getPage( std::string_view _pageName )
{
    return m_pagesStorage.at( _pageName );
}

void GsMainWindow::handleEvent( const Events::TEvent& _tEvent )
{

}

void GsMainWindow::handleEventTimerEllapsed()
{
    m_pEventsDispatcher->processEventQueue();
}

void GsMainWindow::initBackground()
{

    auto createAlignedRect = [parent = lv_disp_get_scr_act(nullptr)]( auto _aligmentType, const lv_style_t* _style )
    {
        lv_obj_t* pObject{ nullptr };
        pObject = lv_obj_create( parent, nullptr );
        lv_obj_set_size(
                pObject
            ,   GsMainWindow::Width
            ,   GsMainWindow::Height / 2
        );

        lv_obj_set_style( pObject, _style );
        lv_obj_align( pObject, nullptr, _aligmentType, 0, 0 );

        return pObject;
    };


    lv_style_copy( &m_iniStyle, &lv_style_plain_color );
    m_iniStyle.body.main_color = m_pThemeController->getMainThemeColor(
            Graphics::Theme::Color::MainThemeDark
        );
    m_iniStyle.body.grad_color = m_iniStyle.body.main_color;

    lv_style_copy(&m_yanStyle, &lv_style_plain_color);
    m_yanStyle.body.main_color = m_pThemeController->getMainThemeColor(
        Graphics::Theme::Color::MainThemeLight
    );
    m_yanStyle.body.grad_color = m_yanStyle.body.main_color;

    m_pIny.reset( createAlignedRect(LV_ALIGN_IN_BOTTOM_MID, &m_iniStyle) );
    m_pYan.reset(createAlignedRect( LV_ALIGN_IN_TOP_MID, &m_yanStyle ) );

    auto createAlignedCircle = [ parent = lv_disp_get_scr_act(nullptr) ](auto _aligmentType, const lv_style_t* _style)
    {
        lv_obj_t* pCircle = lv_obj_create( parent, nullptr );

        lv_obj_set_size(
                pCircle
            ,   GsMainWindow::Width / 2
            ,   GsMainWindow::Height / 2
        );

        lv_obj_set_style( pCircle, _style );
        lv_obj_align( pCircle, nullptr, _aligmentType, 0, 0);

        return pCircle;
    };

    lv_style_copy( &m_iniCircleStyle, &lv_style_plain_color );
   
    m_iniCircleStyle.body.main_color = m_pThemeController->getMainThemeColor(
        Graphics::Theme::Color::MainThemeDark
    );

    m_iniCircleStyle.body.grad_color = m_iniStyle.body.main_color;
    m_iniCircleStyle.body.radius = LV_RADIUS_CIRCLE;

    lv_style_copy( &m_yanCircleStyle, &m_iniCircleStyle );
    m_yanCircleStyle.body.main_color = m_pThemeController->getMainThemeColor(
        Graphics::Theme::Color::MainThemeLight
    );

    m_yanCircleStyle.body.grad_color = m_yanCircleStyle.body.main_color;

    m_pInyCircle.reset( createAlignedCircle( LV_ALIGN_IN_RIGHT_MID, &m_iniCircleStyle ) );
    m_pYanCircle.reset( createAlignedCircle( LV_ALIGN_IN_LEFT_MID, &m_yanCircleStyle ) );
}

void GsMainWindow::initWatchPage()
{
    m_pBatteryWidget = Widgets::createBatteryWidget( getThemeController() );
    m_pBatteryWidgetController = std::move( Widgets::createBatteryWidgetHandler( m_pBatteryWidget ) );

    getEventDispatcher().subscribe(
            Events::EventGroup::Battery
        ,   [ this]( const Events::TEvent& _event )
        {
            m_pBatteryWidgetController->handleEvent( _event );
        }
    );

    m_pPagesSwitch = Widgets::createPagesSwitch( getThemeController() );
    m_pBluetoothWidget = Widgets::createBluetoothWidget( getThemeController() );

    onActivePageChanged.connect(
        [this]( std::string_view _activePage ){
            m_pPagesSwitch->setActivePage( _activePage );
        }
    );

    auto pClockPage = Views::createClockWatchView( getThemeController() );
    pClockPage->addWidget( m_pBatteryWidget );
    pClockPage->addWidget( m_pPagesSwitch );
    pClockPage->addWidget( m_pBluetoothWidget );

    m_pClockPageController = std::move( Views::createPageWatchHandler( pClockPage ) );

    getEventDispatcher().subscribe(
            Events::EventGroup::DateTime
        ,   [ this]( const Events::TEvent& _event )
        {
            m_pClockPageController->handleEvent( _event );
        }
    );

    addPage( std::move( pClockPage ) );
}

void GsMainWindow::initHealthPage()
{
    auto pHealthPage = Views::createHeartrateWatchView( getThemeController() );

    pHealthPage->addWidget( m_pBatteryWidget );
    pHealthPage->addWidget( m_pPagesSwitch );
    pHealthPage->addWidget( m_pBluetoothWidget );

    addPage( std::move( pHealthPage ) );
}

void GsMainWindow::initPlayerPage()
{
    auto pPlayerPage = Views::createPlayerWatchView( getThemeController() );

    pPlayerPage->addWidget(m_pBatteryWidget);
    pPlayerPage->addWidget(m_pPagesSwitch);
    pPlayerPage->addWidget(m_pBluetoothWidget);

    addPage(std::move( pPlayerPage ));
}

Events::EventDispatcher& GsMainWindow::getEventDispatcher()
{
    return *m_pEventsDispatcher;
}

std::weak_ptr<Theme::IThemeController> GsMainWindow::getThemeController() const
{
    return m_pThemeController;
}

std::unique_ptr<IGsMainWindow> createMainWindow()
{
    return std::make_unique<GsMainWindow>();
}

}
