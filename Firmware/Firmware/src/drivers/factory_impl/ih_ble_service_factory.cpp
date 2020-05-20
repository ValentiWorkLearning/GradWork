#include "ih/ih_ble_service_factory.hpp"
#include "ih/ih_ble_battery_service.hpp"

#if defined (USE_BLE_SERVICES)

#include "ble/ble_battery_service.hpp"
#include "ble/ble_datetime_service.hpp"

#endif

namespace Ble::ServiceFactory
{

#if defined (USE_BLE_SERVICES)


class NordicServiceFactory
    :   public IBleServiceFactory
{

public:
    ~NordicServiceFactory()override = default;

public:

    [[nodiscard]] TBatteryServicePtr getBatteryService() override;
    [[nodiscard]] TDateTimeServicePtr getDateTimeService() override;

};

[[nodiscard]] IBleServiceFactory::TDateTimeServicePtr
NordicServiceFactory::getDateTimeService()
{
    return std::make_unique<Ble::DateTimeService::DateTimeServiceNordic>();
}

[[nodiscard]] IBleServiceFactory::TBatteryServicePtr
NordicServiceFactory::getBatteryService()
{
    return std::make_unique<Ble::BatteryService::BatteryLevelService>();
}


#endif

TBleFactoryPtr getBleServiceFactory()
{
#if defined (USE_BLE_SERVICES)
    return std::make_unique<NordicServiceFactory>();
#endif
    return nullptr;
}

}