#include "gs_main_window.hpp"
#include "gs_page_view_object.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_ipage_view_object.hpp"
#include "gs_event_dispatcher.hpp"

#include "gs_theme_controller.hpp"

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

#include "utils/MetaUtils.hpp"

#include <memory>
#include <algorithm>

namespace Graphics::MainWindow
{

GsMainWindow::GsMainWindow(
            std::unique_ptr<Graphics::MainWindow::IMainWindowView>&& _pMainWindowView
        )
    :
        m_currentPageName{}
    ,   m_pEventsDispatcher{ Events::createEventDispatcher() }
    ,   m_pMainWindowView{ std::move( _pMainWindowView ) }
{
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

    m_pagesStorage.push_back( {pageName,std::move( localShared )} );

}

void GsMainWindow::setPageActive( std::string_view _pageName )
{
    if ( getPage( _pageName ).isVisible() )
        return;

    if( !m_currentPageName.empty() )
    {
        auto pPagePtr = getPagePointer( m_currentPageName );
        pPagePtr->hide();
    }

    m_currentPageName = _pageName;

    auto pPagePtr = getPagePointer( m_currentPageName );
    pPagePtr->show();

    onActivePageChanged.emit( m_currentPageName );
}

Graphics::Views::IPageViewObject&
GsMainWindow::getActivePage()
{
    auto pPagePtr = getPagePointer( m_currentPageName );
    return *pPagePtr;
}

const Graphics::Views::IPageViewObject&
GsMainWindow::getActivePage() const
{
    auto pPagePtr = getPagePointer( m_currentPageName );
    return *pPagePtr;
}

const Graphics::Views::IPageViewObject&
GsMainWindow::getPage( std::string_view _pageName )const
{
    auto pPagePtr = getPagePointer( _pageName );
    return *pPagePtr;
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

void GsMainWindow::initWidgets()
{
    m_pBatteryWidget = Widgets::createBatteryWidget( getThemeController() );
    m_pPagesSwitch = Widgets::createPagesSwitch( getThemeController() );
    m_pBluetoothWidget = Widgets::createBluetoothWidget( getThemeController() );

    m_pBluetoothWidgetController = Widgets::createBluetoothWidgetHandler( m_pBluetoothWidget.get() );
    m_pBatteryWidgetController = Widgets::createBatteryWidgetHandler( m_pBatteryWidget.get() );

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
    m_pMainWindowView->getThemeController()->onThemeChanged.connect(
        [this] {
            m_pMainWindowView->resetBackgroundStyle();
            m_pMainWindowView->initBackground();
            auto& activePage = getActivePage();
            activePage.reloadStyle();
        }
    );
}

Views::IPageViewObject*
GsMainWindow::getPagePointer(std::string_view _pageName)
{
    auto it = std::find_if(
        m_pagesStorage.begin()
    ,   m_pagesStorage.end()
    ,   [_pageName]( const auto& _pagePair )
        {
            const auto&[pageName, pagePtr] = _pagePair;
            return pageName == _pageName;
        }
    );

    if( it != m_pagesStorage.end() )
        return it->second.get();
    return nullptr;
}

const Graphics::Views::IPageViewObject*
GsMainWindow::getPagePointer( std::string_view _pageName) const
{
    auto it = std::find_if(
        m_pagesStorage.begin()
    ,   m_pagesStorage.end()
    ,   [_pageName]( const auto& _pagePair )
        {
            const auto&[pageName, pagePtr] = _pagePair;
            return pageName == _pageName;
        }
    );

    if( it != m_pagesStorage.end() )
        return it->second.get();
    return nullptr;
}

Events::EventDispatcher& GsMainWindow::getEventDispatcher()
{
    return *m_pEventsDispatcher;
}

const Theme::IThemeController*
GsMainWindow::getThemeController() const
{
    return m_pMainWindowView->getThemeController();
}

Theme::IThemeController* GsMainWindow::getThemeController()
{
    return m_pMainWindowView->getThemeController();
}

std::unique_ptr<IGsMainWindowModel> createMainWindow(
        std::unique_ptr<Graphics::MainWindow::IMainWindowView>&& _pMainWindowView
    )
{
    return std::make_unique<GsMainWindow>( std::move( _pMainWindowView ) );
}

}
