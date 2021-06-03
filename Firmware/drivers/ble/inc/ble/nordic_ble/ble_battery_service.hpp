#pragma once

#include "ih/drivers/ih_ble_battery_service.hpp"

#include "utils/Noncopyable.hpp"
#include "utils/SimpleSignal.hpp"

#include <cstdint>

namespace Ble::BatteryService
{
inline constexpr std::uint8_t InitialBatteryLevel = 100;

class BatteryLevelService : public IBatteryLevelService
{

public:
    BatteryLevelService() noexcept;
    ~BatteryLevelService() override = default;

public:
    void onBatteryLevelChanged(std::uint8_t _newBatteryLevel) noexcept override;

private:
    void initService() noexcept;
};

} // namespace Ble::BatteryService