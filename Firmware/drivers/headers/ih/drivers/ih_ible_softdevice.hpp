#pragma once

#include "ih/drivers/ih_ble_service_factory.hpp"
#include "utils/SimpleSignal.hpp"

namespace Ble::BatteryService
{
class IBatteryLevelService;
}

namespace Ble::DateTimeService
{
class IDateTimeService;
}

namespace Ble::Stack
{

class IBleSoftDevice
{

public:
    virtual ~IBleSoftDevice() = default;

public:
    virtual Ble::BatteryService::IBatteryLevelService& getBatteryService() noexcept = 0;

    virtual const Ble::BatteryService::IBatteryLevelService& getBatteryService() const noexcept = 0;

    virtual Ble::DateTimeService::IDateTimeService& getDateTimeService() noexcept = 0;

    virtual const Ble::DateTimeService::IDateTimeService& getDateTimeService() const noexcept = 0;

public:
    Simple::Signal<void()> onConnected;
    Simple::Signal<void()> onDisconnected;
};

using TSoftDevicePtr = std::unique_ptr<IBleSoftDevice>;
[[nodiscard]] TSoftDevicePtr createSoftDevice(
    Ble::ServiceFactory::TBleFactoryPtr&& _pServiceCreator) noexcept;

} // namespace Ble::Stack