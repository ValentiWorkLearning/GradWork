#pragma once

#include "ih/sp_ibattery_service.hpp"

namespace ServiceProviders::BatteryService
{

class BatteryServiceFake
    :   public IBatteryLevelAppService
{

public:

    explicit BatteryServiceFake( std::chrono::seconds _measurementPeriod );

    ~BatteryServiceFake()override;

public:

    std::chrono::seconds getMeasurmentPeriod() const override;

    void startBatteryMeasure() override;

private:

    class BatterySimulatorImpl;
    std::unique_ptr<BatterySimulatorImpl> m_pBatterySimImpl;
};

}