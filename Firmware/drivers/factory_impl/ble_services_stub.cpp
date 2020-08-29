#include "ble_services_stub.hpp"

#include "utils/MetaUtils.hpp"
#include "logger/logger_service.hpp"

namespace Ble::BatteryService
{

StubBatteryService::StubBatteryService()
{
    LOG_DEBUG_ENDL( "Initialized DesktopStubBatteryService" );
}

void
StubBatteryService::onBatteryLevelChanged ( std::uint8_t _newBatteryLevel )
{
    LOG_DEBUG("New battery level is:" );
    LOG_DEBUG_ENDL( _newBatteryLevel );
}

}

namespace Ble::DateTimeService
{

StubDateTimeService::StubDateTimeService()
{
    LOG_DEBUG_ENDL( "Initialized StubDateTimeService" );
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
