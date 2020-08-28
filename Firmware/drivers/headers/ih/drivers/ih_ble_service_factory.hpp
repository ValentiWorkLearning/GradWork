#pragma once

#include "ih/drivers/ih_ble_battery_service.hpp"
#include "ih/drivers/ih_ble_dts_service.hpp"

#include "utils/Noncopyable.hpp"

#include <memory>
#include <any>

namespace Ble::BatteryService
{
    class IBatteryLevelService;
}

namespace Ble::DateTimeService
{
    class IDateTimeService;
}

namespace Ble::HeartrateService
{
    class IHeartrateService;
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
    [[nodiscard]] virtual TDateTimeServicePtr getDateTimeService( const std::any& _gattQueue ) = 0;

    using THeartrateServicePtr = TServicePtr<Ble::HeartrateService::IHeartrateService>;
    [[nodiscard]] virtual THeartrateServicePtr getHeartrateService() = 0;

};

using TBleFactoryPtr = std::unique_ptr<IBleServiceFactory>;
TBleFactoryPtr getBleServiceFactory();

}
