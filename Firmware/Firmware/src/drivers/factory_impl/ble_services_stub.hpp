#pragma once

#include "ih/ih_ble_battery_service.hpp"

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
