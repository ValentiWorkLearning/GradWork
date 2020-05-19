#pragma once

#include "Noncopyable.hpp"
#include "ih/ih_ble_battery_service.hpp"

#include <memory>

namespace Ble::BatteryService
{
    class IBatteryLevelService;
};

namespace Ble::ServiceFactory
{

class IBleServiceFactory
    :   private Utils::noncopyable
{
    public:

    virtual ~IBleServiceFactory() = default;

    public:
    using TBatteryServicePtr = std::unique_ptr<Ble::BatteryService::IBatteryLevelService>;
    [[nodiscard]] virtual TBatteryServicePtr getBatteryService() = 0;

};

using TBleFactoryPtr = std::unique_ptr<IBleServiceFactory>;
TBleFactoryPtr getBleServiceFactory();

}