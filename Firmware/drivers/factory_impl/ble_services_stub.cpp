#include "ble_services_stub.hpp"

#include "logger/logger_service.hpp"
#include "utils/MetaUtils.hpp"

namespace Ble::BatteryService
{

StubBatteryService::StubBatteryService() noexcept
{
    LOG_DEBUG("Initialized DesktopStubBatteryService");
}

void StubBatteryService::onBatteryLevelChanged(std::uint8_t _newBatteryLevel) noexcept
{
    LOG_DEBUG("New battery level is:");
    LOG_DEBUG(_newBatteryLevel);
}

} // namespace Ble::BatteryService

namespace Ble::DateTimeService
{

StubDateTimeService::StubDateTimeService() noexcept
{
    LOG_DEBUG("Initialized StubDateTimeService");
}

void StubDateTimeService::handleDiscoveryEvent(const std::any& _pBleDbDiscoveryEvent) noexcept
{
    Meta::UnuseVar(_pBleDbDiscoveryEvent);
}

} // namespace Ble::DateTimeService

namespace Ble::HeartrateService
{

StubHeartrateService::StubHeartrateService() noexcept
{
}

void StubHeartrateService::onHeartrateChanged(std::uint8_t _heartRate) noexcept
{
}

void StubHeartrateService::setSensorLocation(SensorLocation _location) noexcept
{
}

} // namespace Ble::HeartrateService
