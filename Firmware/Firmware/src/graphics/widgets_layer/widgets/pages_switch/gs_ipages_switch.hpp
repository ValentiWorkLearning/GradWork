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

    virtual void mapPageToIndex( std::string_view pageName, const std::uint8_t _pageIndex ) = 0;

    virtual void setActivePage( const std::uint8_t pageIndex ) = 0;
};

};