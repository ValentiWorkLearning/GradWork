#pragma once

#include "utils/SimpleSignal.hpp"

#include <chrono>

namespace ServiceProviders::BatteryService::Settings
{
using namespace std::chrono_literals;
constexpr std::chrono::seconds MeasurmentPeriod = 1s;

constexpr std::uint8_t MinBatteryLevel = 0;
constexpr std::uint8_t MaxBatteryLevel = 100;
} // namespace ServiceProviders::BatteryService::Settings

namespace ServiceProviders::BatteryService
{

class IBatteryLevelAppService
{

public:
    virtual ~IBatteryLevelAppService() = default;

public:
    virtual std::chrono::seconds getMeasurmentPeriod() const noexcept = 0;

    virtual void startBatteryMeasure() noexcept = 0;

    Simple::Signal<void(std::uint8_t)> onBatteryLevelChangedSig;
};

} // namespace ServiceProviders::BatteryService
