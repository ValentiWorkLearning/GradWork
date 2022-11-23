#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <string>

namespace Graphics::Views
{

class IClockWatchPage : public IPageViewObject
{

public:
    virtual void setHours(const std::string& _newHoursValue) noexcept = 0;

    virtual void setMinutes(const std::string& _newMinutesValue) noexcept = 0;

    virtual void setSeconds(const std::string& _newSecondsValue) noexcept = 0;

    virtual void setWeekday(const char* const _newWeekDay) noexcept = 0;

    virtual void setFullDate(const std::string& _fullDate) noexcept = 0;

public:
    static constexpr std::string_view ClockPageName = "ClockPage";
};

} // namespace Graphics::Views
