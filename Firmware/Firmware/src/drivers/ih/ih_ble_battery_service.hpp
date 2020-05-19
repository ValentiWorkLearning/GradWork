#pragma once

#include "Noncopyable.hpp"
#include <cstdint>

namespace Ble::BatteryService
{

class IBatteryLevelService
    :   private Utils::noncopyable
{

public:

    virtual ~IBatteryLevelService() = default;

public:

    virtual void onBatteryLevelChanged ( std::uint8_t _newBatteryLevel ) = 0;

};

}