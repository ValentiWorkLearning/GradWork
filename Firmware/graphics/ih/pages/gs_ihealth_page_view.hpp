#pragma once

#include "ih/gs_ipage_view_object.hpp"

#include <cstdint>
#include <string>

namespace Graphics::Views
{

class IHealthWatchPage : public IPageViewObject
{

public:
    virtual void setStepsCount(std::uint8_t _newStepsValue) noexcept = 0;

    virtual void setHeartrate(std::uint8_t _newHeartrateValue) noexcept = 0;

    virtual void setCalloriesCount(std::uint8_t _newCalloriesCount) noexcept = 0;

public:
    static constexpr std::string_view HealthPageName = "HealthPage";
};

} // namespace Graphics::Views
