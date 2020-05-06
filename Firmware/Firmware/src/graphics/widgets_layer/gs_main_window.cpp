#include "gs_main_window.hpp"
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

#include "widgets/bluetooth/gs_bluetooth_widget_handler.hpp"
#include "widgets/bluetooth/gs_bluetooth_widget.hpp"

#include "pages/clock_page/gs_clock_page_view.hpp"
#include "pages/clock_page/gs_clock_page_handler.hpp"

#include "pages/health_page/gs_health_page_view.hpp"

#include "pages/player_page/gs_player_page_view.hpp"

#include "MetaUtils.hpp"

namespace Graphics::MainWindow
{

GsMainWindow::GsMainWindow()
    :
        m_currentPageName{}
    ,   m_pEventsDispatcher{ std::move( Events::createEventDispatcher() ) }
    ,   m_pThemeController{ std::move( Theme::createThemeController(
                    Theme::ColorTheme::Night
                ,   Width
                ,   Height
                )
            )
        }
    ,   m_iniStyle{}
    ,   m_yanStyle{}
    ,   m_iniCircleStyle{}
    ,   m_yanCircleStyle{}
    ,   maskArea{0,0,240,240}
    ,   radiusParam{}
{
    initMask();
    initBackground();
    initWidgets();
    initWatchPage();
    initHealthPage();
    initPlayerPage();
    initMainWindowSubscriptions();
}

GsMainWindow::~GsMainWindow() = default;

void GsMainWindow::addPage(
        std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    )
{
    auto localShared { std::move( _toAdd ) };
    auto pageName{ localShared->getPageName() };

    localShared->hide();

    m_pagesStorage.insert( {pageName,std::move( localShared )} );

}

void GsMainWindow::setPageActive( std::string_view _pageName )
{
    if ( getPage( _pageName ).isVisible() )
        return;

    if( !m_currentPageName.empty() )
        m_pagesStorage.at( m_currentPageName )->hide();

    m_currentPageName = _pageName;
    m_pagesStorage.at( m_currentPageName )->show();

    onActivePageChanged.emit( m_currentPageName );
}

Graphics::Views::IPageViewObject& GsMainWindow::getActivePage()
{
    return *m_pagesStorage.at( m_currentPageName );
}

Graphics::Views::IPageViewObject& GsMainWindow::getActivePage() const
{
    return *m_pagesStorage.at( m_currentPageName );
}

Graphics::Views::IPageViewObject&
GsMainWindow::getPage( std::string_view _pageName )const
{
    return *m_pagesStorage.at( _pageName );
}

void GsMainWindow::forEachPage(TPageWalker _pageWalker)
{
    for (auto& [pageName, page] : m_pagesStorage) {
        _pageWalker( *page );
    }
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

    auto createAlignedRect = [this]( auto _aligmentType, lv_style_t* _style )
    {
        lv_obj_t* pObject{ nullptr };
        auto parent = m_pObjMask.get();

        pObject = lv_obj_create( parent, nullptr );
        lv_obj_set_size(
                pObject
            ,   GsMainWindow::Width
            ,   GsMainWindow::Height / 2
        );

        lv_obj_add_style( pObject,LV_OBJ_PART_MAIN, _style );
        lv_obj_align( pObject, nullptr, _aligmentType, 0, 0 );

        return pObject;
    };


    const auto MainThemeDark = m_pThemeController->getMainThemeColor(
            Graphics::Theme::Color::MainThemeDark
        );
    const auto MainThemeLight = m_pThemeController->getMainThemeColor(
            Graphics::Theme::Color::MainThemeLight
        );

    lv_style_set_bg_color( &m_iniStyle, LV_STATE_DEFAULT, MainThemeDark );
    lv_style_set_bg_grad_color( &m_iniStyle,LV_STATE_DEFAULT, MainThemeDark );

    lv_style_set_bg_color( &m_yanStyle, LV_STATE_DEFAULT, MainThemeLight );
    lv_style_set_bg_grad_color( &m_yanStyle, LV_STATE_DEFAULT, MainThemeLight );

    m_pIny.reset( createAlignedRect(LV_ALIGN_IN_BOTTOM_MID, &m_iniStyle) );
    m_pYan.reset( createAlignedRect( LV_ALIGN_IN_TOP_MID, &m_yanStyle ) );

    auto createAlignedCircle = [this](auto _aligmentType, lv_style_t* _style)
    {
        auto parent = m_pObjMask.get();
        lv_obj_t* pCircle = lv_obj_create( parent, nullptr );

        lv_obj_set_size(
                pCircle
            ,   GsMainWindow::Width / 2
            ,   GsMainWindow::Height / 2
        );

        lv_obj_add_style( pCircle, LV_OBJ_PART_MAIN, _style );
        lv_obj_align( pCircle, nullptr, _aligmentType, 0, 0);

        return pCircle;
    };

    lv_style_set_bg_color( &m_iniCircleStyle,LV_STATE_DEFAULT, MainThemeDark );
    lv_style_set_border_color( &m_iniCircleStyle, LV_STATE_DEFAULT, MainThemeDark );
    lv_style_set_bg_grad_color( &m_iniCircleStyle, LV_STATE_DEFAULT, MainThemeDark );
    lv_style_set_radius( &m_iniCircleStyle, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE );

    lv_style_copy( &m_yanCircleStyle, &m_iniCircleStyle );

    lv_style_set_bg_color( &m_yanCircleStyle, LV_STATE_DEFAULT, MainThemeLight );
    lv_style_set_border_color( &m_yanCircleStyle, LV_STATE_DEFAULT, MainThemeLight );
    lv_style_set_bg_grad_color( &m_yanCircleStyle, LV_STATE_DEFAULT, MainThemeLight );

    m_pInyCircle.reset( createAlignedCircle( LV_ALIGN_IN_RIGHT_MID, &m_iniCircleStyle ) );
    m_pYanCircle.reset( createAlignedCircle( LV_ALIGN_IN_LEFT_MID, &m_yanCircleStyle ) );
}

void GsMainWindow::resetBackgroundStyle()
{
    Meta::tupleApply(
        [](auto&& _nodeToReset) { 	lv_style_reset(&_nodeToReset); }
        , std::forward_as_tuple(
                m_iniStyle
            ,   m_yanStyle
            ,    m_iniCircleStyle
            ,    m_yanCircleStyle
        )
    );
}

void GsMainWindow::initWidgets()
{
    m_pBatteryWidget = Widgets::createBatteryWidget( getThemeController() );
    m_pPagesSwitch = Widgets::createPagesSwitch( getThemeController() );
    m_pBluetoothWidget = Widgets::createBluetoothWidget( getThemeController() );

    m_pBluetoothWidgetController = std::move( Widgets::createBluetoothWidgetHandler( m_pBluetoothWidget.get() ) );
    m_pBatteryWidgetController = std::move( Widgets::createBatteryWidgetHandler( m_pBatteryWidget.get() ) );

    getEventDispatcher().subscribe(
            Events::EventGroup::BleDevice
        ,   [this]( const Events::TEvent& _event )
        {
            m_pBluetoothWidgetController->handleEvent( _event );
        }
    );

    getEventDispatcher().subscribe(
            Events::EventGroup::Battery
        ,   [this]( const Events::TEvent& _event )
        {
            m_pBatteryWidgetController->handleEvent( _event );
        }
    );

    onActivePageChanged.connect(
        [this]( std::string_view _activePage ){
            m_pPagesSwitch->setActivePage( _activePage );
        }
    );
}

void GsMainWindow::initMask()
{

    m_pObjMask.reset( lv_objmask_create( lv_disp_get_scr_act( nullptr ), nullptr ) );

    const std::uint8_t RoundedArea = 240;
    lv_obj_set_size( m_pObjMask.get(), RoundedArea, RoundedArea );
    lv_obj_align( m_pObjMask.get(), nullptr, LV_ALIGN_CENTER, 0, 0 );

    lv_draw_mask_radius_init( &radiusParam, &maskArea, LV_RADIUS_CIRCLE, false );
    lv_objmask_add_mask( m_pObjMask.get(), &radiusParam );
}

void GsMainWindow::initWatchPage()
{
    auto pClockPage = Views::createClockWatchView( getThemeController() );
    pClockPage->addWidget( m_pBatteryWidget.get() );
    pClockPage->addWidget( m_pPagesSwitch.get() );
    pClockPage->addWidget( m_pBluetoothWidget.get() );

    m_pClockPageController = Views::createPageWatchHandler( pClockPage.get() );

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

    pHealthPage->addWidget( m_pBatteryWidget.get() );
    pHealthPage->addWidget( m_pPagesSwitch.get());
    pHealthPage->addWidget( m_pBluetoothWidget.get());

    addPage( std::move( pHealthPage ) );
}

void GsMainWindow::initPlayerPage()
{
    auto pPlayerPage = Views::createPlayerWatchView( getThemeController() );

    pPlayerPage->addWidget(m_pBatteryWidget.get());
    pPlayerPage->addWidget(m_pPagesSwitch.get());
    pPlayerPage->addWidget(m_pBluetoothWidget.get());

    addPage(std::move( pPlayerPage ));
}

void GsMainWindow::initMainWindowSubscriptions()
{
    m_pThemeController->onThemeChanged.connect(
        [this] {
            resetBackgroundStyle();
            initBackground();
            auto& activePage = getPage(m_currentPageName);
            activePage.reloadStyle();
        }
    );
}

Events::EventDispatcher& GsMainWindow::getEventDispatcher()
{
    return *m_pEventsDispatcher;
}

const Theme::IThemeController* GsMainWindow::getThemeController() const
{
    return m_pThemeController.get();
}

Theme::IThemeController* GsMainWindow::getThemeController()
{
    return m_pThemeController.get();
}

std::unique_ptr<IGsMainWindow> createMainWindow()
{
    return std::make_unique<GsMainWindow>();
}

}
