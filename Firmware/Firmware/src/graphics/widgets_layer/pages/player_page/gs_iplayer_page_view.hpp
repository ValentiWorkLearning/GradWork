#pragma once

#include "gs_page_view_object.hpp"

#include <string>
#include <cstdint>

namespace Graphics::Views
{

class IPlayerWatchPage
    :   public IPageViewObject
{

public:

    virtual void setPause() = 0;

    virtual void setPlaying() = 0;

public:

    static constexpr std::string_view PlayerPageName = "PlayerPage";
};

}