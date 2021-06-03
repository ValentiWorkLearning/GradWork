#pragma once

#include "ih/drivers/ih_ble_battery_service.hpp"
#include "ih/drivers/ih_ble_dts_service.hpp"
#include "ih/drivers/ih_ble_heartrate_service.hpp"

namespace Ble::BatteryService
{

class StubBatteryService : public IBatteryLevelService
{

public:
    StubBatteryService() noexcept;
    ~StubBatteryService() override = default;

public:
    void onBatteryLevelChanged(std::uint8_t _newBatteryLevel) noexcept override;
};

} // namespace Ble::BatteryService

namespace Ble::DateTimeService
{
class StubDateTimeService : public IDateTimeService
{

public:
    StubDateTimeService() noexcept;

public:
    void handleDiscoveryEvent(const std::any& _pBleDbDiscoveryEvent) noexcept override;

public:
    virtual ~StubDateTimeService() override = default;
};

} // namespace Ble::DateTimeService

namespace Ble::HeartrateService
{
class StubHeartrateService : public IHeartrateService
{

public:
    StubHeartrateService() noexcept;

public:
    virtual ~StubHeartrateService() override = default;

public:
    void onHeartrateChanged(std::uint8_t _newHeartrateLevel) noexcept override;

    void setSensorLocation(SensorLocation _sensorLocation) noexcept override;
};

} // namespace Ble::HeartrateService