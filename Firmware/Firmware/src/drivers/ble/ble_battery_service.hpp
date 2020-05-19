#pragma once

#include "ih/ih_ble_battery_service.hpp"

#include "ble.h"
#include "ble_srv_common.h"
#include "ble_bas.h"

#include <cstdint>

#include "Noncopyable.hpp"
#include "SimpleSignal.hpp"

namespace Ble::BatteryService
{

    static constexpr std::uint16_t ServiceUuid = BLE_UUID_BATTERY_SERVICE;
    static constexpr std::uint8_t ServiceType = BLE_UUID_TYPE_BLE;

    static constexpr std::uint8_t InitialBatteryLevel = 100;

class BatteryLevelService
    :   public IBatteryLevelService
{

public:

    BatteryLevelService();
    ~BatteryLevelService()override = default;

public:

    void onBatteryLevelChanged ( std::uint8_t _newBatteryLevel ) override;

private:

    void initService();
};


}