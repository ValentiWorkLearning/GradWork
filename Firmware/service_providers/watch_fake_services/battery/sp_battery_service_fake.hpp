#pragma once

#include "ih/sp_ibattery_service.hpp"

namespace ServiceProviders::BatteryService
{

class BatteryServiceFake : public IBatteryLevelAppService
{

public:
    explicit BatteryServiceFake(std::chrono::seconds _measurementPeriod) noexcept;

    ~BatteryServiceFake() override;

public:
    std::chrono::seconds getMeasurmentPeriod() const noexcept override;

    void startBatteryMeasure() noexcept override;

private:
    class BatterySimulatorImpl;
    std::unique_ptr<BatterySimulatorImpl> m_pBatterySimImpl;
};

} // namespace ServiceProviders::BatteryService