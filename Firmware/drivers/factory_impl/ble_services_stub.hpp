#pragma once

#include "ih/drivers/ih_ble_battery_service.hpp"
#include "ih/drivers/ih_ble_dts_service.hpp"
#include "ih/drivers/ih_ble_heartrate_service.hpp"

namespace Ble::BatteryService
{

class StubBatteryService
    :   public IBatteryLevelService
{

public:

    StubBatteryService();
    ~StubBatteryService()override = default;

public:

    void onBatteryLevelChanged ( std::uint8_t _newBatteryLevel ) override;

};

}


namespace Ble::DateTimeService
{
class StubDateTimeService
    :   public IDateTimeService
{

public:

    StubDateTimeService();

public:

    void handleDiscoveryEvent( const std::any& _pBleDbDiscoveryEvent )override;

public:

    virtual ~StubDateTimeService()override = default;
};

}


namespace Ble::HeartrateService
{
class StubHeartrateService
    :   public IHeartrateService
{

public:

    StubHeartrateService();

public:

    virtual ~StubHeartrateService()override = default;

public:
    void onHeartrateChanged ( std::uint8_t _newHeartrateLevel ) override;

    void setSensorLocation( SensorLocation _sensorLocation ) override;
};

}