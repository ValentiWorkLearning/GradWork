#include "inc/ble/ble_desktop_softdevice.hpp"

#include <optional>

namespace Ble::Stack
{

DesktopBleStackKeeper::DesktopBleStackKeeper( ServiceFactory::TBleFactoryPtr&& _pServiceCreator )
    : m_isConnected{ false }
    , m_pServiceCreator{ std::move(_pServiceCreator) }
{
    m_batteryService = m_pServiceCreator->getBatteryService();
    m_dateTimeService = m_pServiceCreator->getDateTimeService( std::nullopt );
}

Ble::BatteryService::IBatteryLevelService&
DesktopBleStackKeeper::getBatteryService()
{
    return *m_batteryService.get();
}

const Ble::BatteryService::IBatteryLevelService&
DesktopBleStackKeeper::getBatteryService() const
{
    return *m_batteryService.get();
}


Ble::DateTimeService::IDateTimeService&
DesktopBleStackKeeper::getDateTimeService()
{
    return *m_dateTimeService.get();
}

const Ble::DateTimeService::IDateTimeService&
DesktopBleStackKeeper::getDateTimeService() const
{
    return *m_dateTimeService.get();
}

std::unique_ptr<IBleSoftDevice>
createBleStackKeeper( ServiceFactory::TBleFactoryPtr&& _pServiceCreator )
{
    return std::make_unique<DesktopBleStackKeeper>( std::move( _pServiceCreator ) );
}


}