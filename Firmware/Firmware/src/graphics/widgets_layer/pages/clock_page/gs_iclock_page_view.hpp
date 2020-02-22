#pragma once

#include "gs_page_view_object.hpp"

#include <string>

namespace Graphics::Views
{

class IClockWatchPage
    :   public IPageViewObject
{

public:

    virtual void setHours( std::string_view _newHoursValue ) = 0;

    virtual void setMinutes( std::string_view _newMinutesValue ) = 0;

    virtual void setSeconds( std::string_view _newSecondsValue ) = 0;

    virtual void setWeekday( std::string_view _newWeekDay ) = 0;

    virtual void setFullDate( std::string_view _fullDate ) = 0;

public:

    static constexpr std::string_view ClockPageName = "ClockPage";
};

}