#include "ble_services_stub.hpp"

#include "logger_service.hpp"

namespace Ble::BatteryService
{

StubBatteryService::StubBatteryService()
{
    Logger::Instance().logDebugEndl( "Initialized DesktopStubBatteryService" );
}

void
StubBatteryService::onBatteryLevelChanged ( std::uint8_t _newBatteryLevel )
{
    Logger::Instance().logDebug("New battery level is:" );
    Logger::Instance().logDebugEndl( _newBatteryLevel );
}

}