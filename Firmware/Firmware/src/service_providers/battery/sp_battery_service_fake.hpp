#pragma once

#include "ih/sp_ibattery_service.hpp"

#include "FastPimpl.hpp"
#include "Platform.hpp"

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

    static constexpr inline  std::size_t kImplSize =  Platform::BatteryImplSize;
    static constexpr inline  std::size_t kImplAlignment = Platform::BatteryAlignment;

private:

    class BatterySimulatorImpl;
    Utils::FastPimpl<BatterySimulatorImpl,kImplSize,kImplAlignment> m_pBatterySimImpl;
};

}