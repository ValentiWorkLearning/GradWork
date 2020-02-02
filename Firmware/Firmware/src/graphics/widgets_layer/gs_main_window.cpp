#include "gs_main_window.hpp"
#include "gs_page_view_object.hpp"

namespace Graphics::MainWindow
{

GsMainWindow::GsMainWindow()
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

void GsMainWindow::handleEvent( const EventDispatcher::Events::Event& _tEvent )
{

}

void GsMainWindow::handleEventTimerEllapsed()
{

}

void GsMainWindow::initBackground()
{

}

void GsMainWindow::initEventDispatcher()
{
}

std::unique_ptr<IGsMainWindow> createMainWindow()
{
    return std::make_unique<GsMainWindow>();
}

}