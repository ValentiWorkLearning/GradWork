#pragma once

#include "ih/ih_ible_softdevice.hpp"
#include "ih/ih_ble_battery_service.hpp"
#include "ih/ih_ble_dts_service.hpp"
#include "ih/ih_ble_service_factory.hpp"

#include <atomic>

namespace Ble::Stack
{
class DesktopBleStackKeeper
    :   public IBleSoftDevice
{

public:

    DesktopBleStackKeeper( ServiceFactory::TBleFactoryPtr&& _pServiceCreator );
    ~DesktopBleStackKeeper()override = default;

public:

    Ble::BatteryService::IBatteryLevelService& getBatteryService() override;

    const Ble::BatteryService::IBatteryLevelService& getBatteryService() const override;

    Ble::DateTimeService::IDateTimeService& getDateTimeService() override;

    const Ble::DateTimeService::IDateTimeService& getDateTimeService() const override;

private:

    std::atomic<bool> m_isConnected;

    ServiceFactory::TBleFactoryPtr m_pServiceCreator;
    Ble::ServiceFactory::IBleServiceFactory::TBatteryServicePtr m_batteryService;
    Ble::ServiceFactory::IBleServiceFactory::TDateTimeServicePtr m_dateTimeService;
};

std::unique_ptr<IBleSoftDevice>
createBleStackKeeper( ServiceFactory::TBleFactoryPtr&& _pServiceCreator );

}