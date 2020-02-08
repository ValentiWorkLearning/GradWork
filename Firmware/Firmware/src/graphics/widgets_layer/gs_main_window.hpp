#pragma once

#include "ih/gs_imain_window.hpp"
#include "ih/gs_events.hpp"

namespace Graphics::Events
{
    class EventDispatcher;
}

#include <vector>

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

    using TPagePtr = std::unique_ptr<Graphics::Views::IPageViewObject>;
    using TPagesStorage = std::vector<TPagePtr>;

    std::unique_ptr<Events::EventDispatcher> m_pEventsDispatcher;
    TPagesStorage m_pagesStorage;

};

std::unique_ptr<IGsMainWindow> createMainWindow();

};
