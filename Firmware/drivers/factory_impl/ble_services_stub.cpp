#include "ble_services_stub.hpp"

#include "utils/MetaUtils.hpp"
#include "logger/logger_service.hpp"

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

namespace Ble::DateTimeService
{

StubDateTimeService::StubDateTimeService()
{
    Logger::Instance().logDebugEndl( "Initialized StubDateTimeService" );
}


void
StubDateTimeService::handleDiscoveryEvent( const std::any& _pBleDbDiscoveryEvent )
{
    Meta::UnuseVar( _pBleDbDiscoveryEvent );
}

}


namespace Ble::HeartrateService
{

void
StubHeartrateService::onHeartrateChanged( std::uint8_t _heartRate )
{
}

void
StubHeartrateService::setSensorLocation(SensorLocation _location)
{
}

}