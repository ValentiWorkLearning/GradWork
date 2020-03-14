#pragma once

#include "ih/gs_imain_window.hpp"
#include "ih/gs_itheme_controller.hpp"
#include "ih/gs_events.hpp"

#include "MetaUtils.hpp"

#include <vector>
#include <string>
#include <map>

namespace Graphics::Events
{
    class EventDispatcher;
}

namespace Graphics::Theme
{
    class IThemeController;
}


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
    :   public IGsMainWindow
{

public:

    GsMainWindow();
    ~GsMainWindow() override;

public:

    void handleEvent( const Events::TEvent& _tEvent ) override;

    void addPage(
        std::shared_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    ) override;

    void setPageActive( std::string_view _pageName ) override;

    std::shared_ptr<Graphics::Views::IPageViewObject>
        getPage( std::string_view _pageName ) override;

    void handleEventTimerEllapsed() override;

    Events::EventDispatcher& getEventDispatcher() override;

    std::weak_ptr<Theme::IThemeController> getThemeController() const override;

private:

    void initBackground();

    void initWatchPage();

    void initHealthPage();

    void initPlayerPage();

private:

    static const inline std::uint32_t Width = LV_HOR_RES;
    static const inline std::uint32_t Height = LV_VER_RES;

private:

    using TPagePtr = std::shared_ptr<Graphics::Views::IPageViewObject>;
    using TPagesStorage = std::map<std::string_view,TPagePtr>;

    std::string_view m_currentPageName;

    std::unique_ptr<Events::EventDispatcher> m_pEventsDispatcher;
    std::shared_ptr<Theme::IThemeController> m_pThemeController;

    TPagesStorage m_pagesStorage;

private:

    lv_style_t m_iniStyle;
    lv_style_t m_yanStyle;
    lv_style_t m_iniCircleStyle;
    lv_style_t m_yanCircleStyle;

    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pIny;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pInyCircle;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pYan;
    Meta::PointerWrapper<lv_obj_t, lv_obj_del> m_pYanCircle;

private:

    std::shared_ptr<Graphics::Widgets::IBatteryWidget> m_pBatteryWidget;
    std::shared_ptr<Graphics::Widgets::IPagesSwitch> m_pPagesSwitch;
    std::shared_ptr<Graphics::Widgets::IBluetoothWidget> m_pBluetoothWidget;

    std::unique_ptr<Graphics::IEventHandler> m_pBatteryWidgetController;
    std::unique_ptr<Graphics::IEventHandler> m_pClockPageController;

};

std::unique_ptr<IGsMainWindow> createMainWindow();

};
