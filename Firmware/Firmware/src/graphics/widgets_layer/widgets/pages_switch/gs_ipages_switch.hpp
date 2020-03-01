#pragma once

#include "gs_iwidget_object.hpp"

#include <cstdint>
#include <string>

namespace Graphics::Widgets
{

class IPagesSwitch
    :   public IWidgetObject
{

public:

    virtual void setActivePage(std ::string_view pageName ) = 0;
};

};