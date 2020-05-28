#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <string>

namespace Graphics::Views
{

class IClockWatchPage
    :   public IPageViewObject
{

public:

    virtual void setHours( const std::string& _newHoursValue ) = 0;

    virtual void setMinutes( const std::string& _newMinutesValue ) = 0;

    virtual void setSeconds( const std::string& _newSecondsValue ) = 0;

    virtual void setWeekday( std::string_view _newWeekDay ) = 0;

    virtual void setFullDate( const std::string& _fullDate ) = 0;

public:

    static constexpr std::string_view ClockPageName = "ClockPage";
};

}
