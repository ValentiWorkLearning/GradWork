#include "SimpleSignal.hpp"

namespace Ble::BatteryService
{
    class BatteryLevelService;    
}

namespace Ble::Stack
{


class IBleSoftDevice
{

public:

    virtual Ble::BatteryService::BatteryLevelService& getBatteryService() = 0;

    virtual const Ble::BatteryService::BatteryLevelService& getBatteryService() const = 0;

public:

    Simple::Signal<void()> onConnected;
    Simple::Signal<void()> onDisconnected;

};

}