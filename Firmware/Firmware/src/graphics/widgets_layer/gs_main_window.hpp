#pragma once

#include "ih/gs_imain_window.hpp"

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

    void handleEvent( const EventDispatcher::Events::Event& _tEvent ) override;

    void addPage( std::unique_ptr<Graphics::Views::IPageViewObject>&& _toAdd ) override;

    void handleEventTimerEllapsed() override;

private:

    void initBackground();

    void initEventDispatcher();

private:

    using TPagePtr = std::unique_ptr<Graphics::Views::IPageViewObject>;
    using TPagesStorage = std::vector<TPagePtr>;

    TPagesStorage m_pagesStorage;

};

std::unique_ptr<IGsMainWindow> createMainWindow();

};