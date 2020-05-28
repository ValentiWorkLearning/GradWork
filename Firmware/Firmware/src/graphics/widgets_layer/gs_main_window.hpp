#pragma once

#include "ih/gs_imain_window.hpp"
#include "ih/gs_itheme_controller.hpp"
#include "ih/gs_events.hpp"

#include "MetaUtils.hpp"

#include <vector>
#include <string>
#include <map>

namespace Graphics::Widgets
{
    class IBatteryWidget;
    class IPagesSwitch;
    class IBluetoothWidget;
}

namespace Graphics
{
    class IEventHandler;
}

namespace Graphics::MainWindow
{

class GsMainWindow
    :   public IGsMainWindowModel
{

public:

    GsMainWindow( std::unique_ptr<Graphics::MainWindow::IMainWindowView>&& _pMainWindowView );
    ~GsMainWindow() override;

public:

    void handleEvent( const Events::TEvent& _tEvent ) override;

    void addPage(
        std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    ) override;

    void setPageActive( std::string_view _pageName ) override;

    Graphics::Views::IPageViewObject& getActivePage() override;

    Graphics::Views::IPageViewObject& getActivePage()const override;

    Graphics::Views::IPageViewObject&
        getPage( std::string_view _pageName )const override;

    void forEachPage(TPageWalker _pageWalker) override;

public:

    void handleEventTimerEllapsed() override;

    Events::EventDispatcher& getEventDispatcher() override;

    const Theme::IThemeController* getThemeController() const override;

    Theme::IThemeController* getThemeController() override;

private:

    void initWidgets();

    void initWatchPage();

    void initHealthPage();

    void initPlayerPage();

    void initMainWindowSubscriptions();

private:

    using TPagePtr = std::unique_ptr<Graphics::Views::IPageViewObject>;
    using TPagesStorage = std::map<std::string_view,TPagePtr>;

    std::string_view m_currentPageName;

    std::unique_ptr<Events::EventDispatcher> m_pEventsDispatcher;

    TPagesStorage m_pagesStorage;

private:

    std::unique_ptr<Graphics::MainWindow::IMainWindowView> m_pMainWindowView;
    std::unique_ptr<Graphics::Widgets::IBatteryWidget> m_pBatteryWidget;
    std::unique_ptr<Graphics::Widgets::IPagesSwitch> m_pPagesSwitch;
    std::unique_ptr<Graphics::Widgets::IBluetoothWidget> m_pBluetoothWidget;

    std::unique_ptr<Graphics::IEventHandler> m_pBatteryWidgetController;
    std::unique_ptr<Graphics::IEventHandler> m_pBluetoothWidgetController;
    std::unique_ptr<Graphics::IEventHandler> m_pClockPageController;

};

std::unique_ptr<IGsMainWindowModel> createMainWindow(
        std::unique_ptr<Graphics::MainWindow::IMainWindowView>&& _pMainWindowView
);

};
