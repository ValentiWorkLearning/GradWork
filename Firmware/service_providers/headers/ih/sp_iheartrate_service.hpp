#pragma once

#include "utils/SimpleSignal.hpp"

#include <chrono>

namespace ServiceProviders::HeartrateService::Settings
{
    using namespace std::chrono_literals;
    constexpr std::chrono::seconds MeasurmentPeriod = 12s;
}

namespace ServiceProviders::HeartrateService
{

class IHeartrateService
{

public:

    virtual ~IHeartrateService() = default;

    virtual void startMeasure() = 0;

    Simple::Signal<void()> onMeasureStarted;
    Simple::Signal<void()> onMeasureFailed;

    Simple::Signal<void(std::uint8_t)> onHeartrateDataReady;
};

} // namespace ServiceProviders::BatteryService
