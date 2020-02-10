#pragma once

#include "gs_page_view_object.hpp"

namespace Graphics::Views
{

class ClockWatch
    :   public PageViewObject
{

public:
    ~ClockWatch() override = default;

public:
    
    void show() override;

    void hide() override;

private:

};


std::unique_ptr<IPageViewObject> createClockWatchView();

}