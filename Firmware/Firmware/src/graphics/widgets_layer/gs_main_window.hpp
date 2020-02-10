#pragma once

#include "ih/gs_imain_window.hpp"
#include "ih/gs_itheme_controller.hpp"
#include "ih/gs_events.hpp"

#include "MetaUtils.hpp"

#include <vector>

namespace Graphics::Events
{
    class EventDispatcher;
}

namespace Graphics::Theme
{
    class IThemeController;
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

    void addPage( std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd ) override;

    void handleEventTimerEllapsed() override;

    Events::EventDispatcher& getEventDispatcher() override;

private:

    void initBackground();

private:

    static const inline std::uint32_t Width = LV_HOR_RES;
    static const inline std::uint32_t Height = LV_VER_RES;

private:

    using TPagePtr = std::unique_ptr<Graphics::Views::IPageViewObject>;
    using TPagesStorage = std::vector<TPagePtr>;

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
};

std::unique_ptr<IGsMainWindow> createMainWindow();

};
