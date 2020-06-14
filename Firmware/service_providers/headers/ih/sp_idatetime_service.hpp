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

    virtual void launchService() = 0;

    virtual void calibrateSource() = 0;

    virtual void syncronizeWithBleDts() = 0;

public:

    Simple::Signal<void(TimeWrapper)> onDateTimeChanged;
};

} // namespace ServiceProviders::BatteryService
