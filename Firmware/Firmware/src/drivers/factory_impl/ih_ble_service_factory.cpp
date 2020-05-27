#include "ih/ih_ble_service_factory.hpp"
#include "ih/ih_ble_battery_service.hpp"

#include "MetaUtils.hpp"

#if defined (USE_BLE_SERVICES)

#include "ble/ble_battery_service.hpp"
#include "ble/ble_datetime_service.hpp"

#elif defined (USE_DESKTOP_SIMULATOR)
#include "drivers/factory_impl/ble_services_stub.hpp"
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
    [[nodiscard]] TDateTimeServicePtr getDateTimeService( const std::any& _gattQueue ) override;

};

[[nodiscard]] IBleServiceFactory::TDateTimeServicePtr
NordicServiceFactory::getDateTimeService( const std::any& _gattQueue )
{
    return std::make_unique<Ble::DateTimeService::DateTimeServiceNordic>( _gattQueue );
}

[[nodiscard]] IBleServiceFactory::TBatteryServicePtr
NordicServiceFactory::getBatteryService()
{
    return std::make_unique<Ble::BatteryService::BatteryLevelService>();
}

#elif defined (USE_DESKTOP_SIMULATOR)

class DesktopFakeBleServiceFactory
    :   public IBleServiceFactory
{

public:
    ~DesktopFakeBleServiceFactory()override = default;

public:

    [[nodiscard]] TBatteryServicePtr getBatteryService() override;
    [[nodiscard]] TDateTimeServicePtr getDateTimeService( const std::any& _gattQueue ) override;
};


[[nodiscard]] IBleServiceFactory::TDateTimeServicePtr
DesktopFakeBleServiceFactory::getDateTimeService( const std::any& _gattQueue )
{
    Meta::UnuseVar( _gattQueue );
    return std::make_unique<Ble::DateTimeService::StubDateTimeService>();
}

[[nodiscard]] IBleServiceFactory::TBatteryServicePtr
DesktopFakeBleServiceFactory::getBatteryService()
{
    return std::make_unique<Ble::BatteryService::StubBatteryService>();
}

#endif




TBleFactoryPtr getBleServiceFactory()
{
#if defined (USE_BLE_SERVICES)
    return std::make_unique<NordicServiceFactory>();
#elif defined (USE_DESKTOP_SIMULATOR)
    return std::make_unique<DesktopFakeBleServiceFactory>();
#endif
}

}