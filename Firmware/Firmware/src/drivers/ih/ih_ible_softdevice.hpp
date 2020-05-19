#pragma once

#include "SimpleSignal.hpp"
#include "ih/ih_ble_service_factory.hpp"

namespace Ble::BatteryService
{
    class IBatteryLevelService;
}

namespace Ble::Stack
{


class IBleSoftDevice
{

public:

    virtual ~IBleSoftDevice() = default;

public:

    virtual Ble::BatteryService::IBatteryLevelService& getBatteryService() = 0;

    virtual const Ble::BatteryService::IBatteryLevelService& getBatteryService() const = 0;

public:

    Simple::Signal<void()> onConnected;
    Simple::Signal<void()> onDisconnected;

};

using TSoftDevicePtr = std::unique_ptr<IBleSoftDevice>;
[[nodiscard]]
TSoftDevicePtr createSoftDevice( Ble::ServiceFactory::TBleFactoryPtr&& _pServiceCreator );


}