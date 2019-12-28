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
    :   private Utils::noncopyable
{

public:

    BatteryLevelService();
    ~BatteryLevelService() = default;

    void onBatteryLevelChanged ( std::uint8_t _newBatteryLevel );

private:

    void initService();
};


}