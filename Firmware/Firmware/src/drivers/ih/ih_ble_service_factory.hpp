#pragma once

#include "Noncopyable.hpp"
#include "ih/ih_ble_battery_service.hpp"

#include <memory>

namespace Ble::BatteryService
{
    class IBatteryLevelService;
}

namespace Ble::DateTimeService
{
    class IDateTimeService;
}

namespace Ble::ServiceFactory
{

class IBleServiceFactory
    :   private Utils::noncopyable
{
    public:

    virtual ~IBleServiceFactory() = default;

    public:

    template< typename TService >
    using TServicePtr = std::unique_ptr<TService>;

    using TBatteryServicePtr = TServicePtr<Ble::BatteryService::IBatteryLevelService>;
    [[nodiscard]] virtual TBatteryServicePtr getBatteryService() = 0;

    using TDateTimeServicePtr = TServicePtr<Ble::DateTimeService::IDateTimeService>;
    [[nodiscard]] virtual TDateTimeServicePtr getDateTimeService() = 0;

};

using TBleFactoryPtr = std::unique_ptr<IBleServiceFactory>;
TBleFactoryPtr getBleServiceFactory();

}