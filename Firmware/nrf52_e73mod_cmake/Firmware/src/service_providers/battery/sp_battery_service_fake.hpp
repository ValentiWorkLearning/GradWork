#pragma once

#include "ih/sp_ibattery_service.hpp"

#include "sensorsim.h"

namespace ServiceProviders::BatteryService
{

class BatteryServiceFake
    :   public IBatteryLevelAppService
{

public:

    explicit BatteryServiceFake( std::chrono::seconds _measurementPeriod );

    void setMeasurmentPeriod( const std::chrono::seconds _measurementPeriod ) override;

    std::chrono::seconds getMeasurmentPeriod() const override;

    ~BatteryServiceFake()override = default;


protected:

    void measureBatteryLevel() override;

private:

    void timerExpiredHandler( void * _pContext );

    void initSimulator();

    void initTimer();

private:

    static constexpr std::uint8_t BatteryIncrement = 1;
    static constexpr std::uint8_t FakeMinBatteryLevel = 65;
    static constexpr std::uint8_t FakeMaxBatteryLevel = 100;

private:

    std::uint8_t m_batteryLevel;

    /**< Battery Level sensor simulator configuration. */
    sensorsim_cfg_t   m_simulatorConfig;
    /**< Battery Level sensor simulator state. */
    sensorsim_state_t m_simulatorState;

    std::chrono::seconds m_measuringPeriod;
};

}