#pragma once

#include "ih/ih_ble_battery_service.hpp"
#include "ih/ih_ble_dts_service.hpp"

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