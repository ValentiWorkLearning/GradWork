#include "ih/ih_ible_softdevice.hpp"

#if defined (USE_BLE_SERVICES)

#include "ble/ble_softdevice.hpp"
#include "ble/ble_custom_service.hpp"

#elif defined (USE_DESKTOP_SIMULATOR)
#include "drivers/ble/ble_desktop_softdevice.hpp"
#endif

namespace Ble::Stack
{

TSoftDevicePtr createSoftDevice(
    Ble::ServiceFactory::TBleFactoryPtr&& _pServiceCreator
)
{
    return Ble::Stack::createBleStackKeeper(
        std::move( _pServiceCreator )
    );
}


}