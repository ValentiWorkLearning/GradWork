#pragma once

#include "gs_iwidget_object.hpp"

#include <cstdint>

namespace Graphics::Widgets
{

class IPagesSwitch
    :   public IWidgetObject
{

public:

    virtual void setActivePage( const std::uint8_t pageIndex );
}

};