#pragma once

#include "utils/SimpleSignal.hpp"
#include "utils/TimeWrapper.hpp"

namespace ServiceProviders::DateTimeService::Settings
{
}

namespace ServiceProviders::DateTimeService
{

class IDateTimeService
{

public:
    virtual ~IDateTimeService() = default;

    virtual void launchService() noexcept = 0;

    virtual void calibrateSource() noexcept = 0;

    virtual void syncronizeWithBleDts() noexcept = 0;

public:
    Simple::Signal<void(TimeWrapper)> onDateTimeChanged;
};

} // namespace ServiceProviders::DateTimeService
