#include "gs_main_window.hpp"
#include "gs_page_view_object.hpp"

#include "gs_events.hpp"
#include "gs_event_dispatcher.hpp"

namespace Graphics::MainWindow
{

GsMainWindow::GsMainWindow()
    :   m_pEventsDispatcher{ std::move( Events::createEventDispatcher() ) }
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
