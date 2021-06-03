#include "ih/drivers/ih_ble_service_factory.hpp"
#include "ih/drivers/ih_ble_battery_service.hpp"

#include "utils/MetaUtils.hpp"

#if defined(USE_BLE_SERVICES)
#include "ble/nordic_ble/ble_battery_service.hpp"
#include "ble/nordic_ble/ble_datetime_service.hpp"
#include "ble/nordic_ble/ble_heartrate_service.hpp"

#elif defined(USE_DESKTOP_SIMULATOR)
#include "ble_services_stub.hpp"
#endif

namespace Ble::ServiceFactory
{

#if defined(USE_BLE_SERVICES)

class NordicServiceFactory : public IBleServiceFactory
{

public:
    ~NordicServiceFactory() override = default;

public:
    [[nodiscard]] TBatteryServicePtr getBatteryService() noexcept override;
    [[nodiscard]] TDateTimeServicePtr getDateTimeService(
        const std::any& _gattQueue) noexcept override;
    [[nodiscard]] THeartrateServicePtr getHeartrateService() noexcept override;
};

[[nodiscard]] IBleServiceFactory::TDateTimeServicePtr NordicServiceFactory::getDateTimeService(
    const std::any& _gattQueue) noexcept
{
    return std::make_unique<Ble::DateTimeService::DateTimeServiceNordic>(_gattQueue);
}

[[nodiscard]] IBleServiceFactory::TBatteryServicePtr NordicServiceFactory::
    getBatteryService() noexcept
{
    return std::make_unique<Ble::BatteryService::BatteryLevelService>();
}

[[nodiscard]] IBleServiceFactory::THeartrateServicePtr NordicServiceFactory::
    getHeartrateService() noexcept
{
    return std::make_unique<Ble::HeartrateService::NordicHeartrateService>();
}

#elif defined(USE_DESKTOP_SIMULATOR)

class DesktopFakeBleServiceFactory : public IBleServiceFactory
{

public:
    ~DesktopFakeBleServiceFactory() override = default;

public:
    [[nodiscard]] TBatteryServicePtr getBatteryService() noexcept override;
    [[nodiscard]] TDateTimeServicePtr getDateTimeService(
        const std::any& _gattQueue) noexcept override;
    [[nodiscard]] THeartrateServicePtr getHeartrateService() noexcept override;
};

[[nodiscard]] IBleServiceFactory::TDateTimeServicePtr DesktopFakeBleServiceFactory::
    getDateTimeService(const std::any& _gattQueue) noexcept
{
    Meta::UnuseVar(_gattQueue);
    return std::make_unique<Ble::DateTimeService::StubDateTimeService>();
}

[[nodiscard]] IBleServiceFactory::TBatteryServicePtr DesktopFakeBleServiceFactory::
    getBatteryService() noexcept
{
    return std::make_unique<Ble::BatteryService::StubBatteryService>();
}

[[nodiscard]] IBleServiceFactory::THeartrateServicePtr DesktopFakeBleServiceFactory::
    getHeartrateService() noexcept
{
    return std::make_unique<Ble::HeartrateService::StubHeartrateService>();
}
#endif

TBleFactoryPtr getBleServiceFactory() noexcept
{
#if defined(USE_BLE_SERVICES)
    return std::make_unique<NordicServiceFactory>();
#elif defined(USE_DESKTOP_SIMULATOR)
    return std::make_unique<DesktopFakeBleServiceFactory>();
#endif
}

} // namespace Ble::ServiceFactory