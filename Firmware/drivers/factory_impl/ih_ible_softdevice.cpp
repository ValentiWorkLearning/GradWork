#include "ih/drivers/ih_ible_softdevice.hpp"

#if defined (USE_BLE_SERVICES)
#include "ble/nordic_ble/ble_softdevice.hpp"
#include "ble/nordic_ble/ble_custom_service.hpp"

#elif defined (USE_DESKTOP_SIMULATOR)
#include "desktop_ble/ble_desktop_softdevice.hpp"
#endif

namespace Ble::Stack
{

TSoftDevicePtr createSoftDevice(
    Ble::ServiceFactory::TBleFactoryPtr&& _pServiceCreator
)noexcept
{
    return Ble::Stack::createBleStackKeeper(
        std::move( _pServiceCreator )
    );
}


}