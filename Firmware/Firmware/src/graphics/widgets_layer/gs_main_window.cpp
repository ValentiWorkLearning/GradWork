#include "gs_main_window.hpp"
#include "gs_page_view_object.hpp"

#include "gs_events.hpp"
#include "gs_event_dispatcher.hpp"

#include "gs_theme_controller.hpp"

namespace Graphics::MainWindow
{

GsMainWindow::GsMainWindow()
    :   m_pEventsDispatcher{ std::move( Events::createEventDispatcher() ) }
    ,   m_pThemeController{ std::move( Theme::createThemeController( Theme::ColorTheme::Pastele ) ) }
{
    initBackground();
}

GsMainWindow::~GsMainWindow() = default;

void GsMainWindow::addPage(
        std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd
    )
{
    m_pagesStorage.push_back( std::move( _toAdd ) );
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

Events::EventDispatcher& GsMainWindow::getEventDispatcher()
{
    return *m_pEventsDispatcher;
}

std::unique_ptr<IGsMainWindow> createMainWindow()
{
    return std::make_unique<GsMainWindow>();
}

}
