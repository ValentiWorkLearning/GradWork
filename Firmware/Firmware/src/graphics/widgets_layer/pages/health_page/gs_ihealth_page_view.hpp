#pragma once

#include "gs_page_view_object.hpp"

#include <string>
#include <cstdint>

namespace Graphics::Views
{

class IHealthWatchPage
    :   public IPageViewObject
{

public:

    virtual void setStepsCount( std::uint8_t _newStepsValue ) = 0;

    virtual void setHeartrate( std::uint8_t _newHeartrateValue ) = 0;

    virtual void setCalloriesCount( std::uint8_t _newCalloriesCount ) = 0;

public:

    static constexpr std::string_view HealthPageName = "HealthPage";
};

}