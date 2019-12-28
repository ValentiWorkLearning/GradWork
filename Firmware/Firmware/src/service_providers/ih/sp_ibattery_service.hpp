#pragma once

#include "SimpleSignal.hpp"

#include <chrono>

namespace ServiceProviders::BatteryService::Settings
{
    using namespace std::chrono_literals;
    constexpr std::chrono::seconds MeasurmentPeriod = 2s;

    constexpr std::uint8_t MinBatteryLevel = 0;
    constexpr std::uint8_t MaxBatteryLevel = 100;
}

namespace ServiceProviders::BatteryService
{

class IBatteryLevelAppService
{

public:

    virtual void setMeasurmentPeriod( const std::chrono::seconds _measurementPeriod ) = 0;

    virtual std::chrono::seconds getMeasurmentPeriod() const = 0;

    virtual ~IBatteryLevelAppService() = default;

    Simple::Signal<void(std::uint8_t)> onBatteryLevelChangedSig;

protected:

    virtual void measureBatteryLevel() = 0;

};

} // namespace ServiceProviders::BatteryService
