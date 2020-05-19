#include "ih/ih_ible_softdevice.hpp"

#if defined (USE_BLE_SERVICES)

#include "ble/ble_softdevice.hpp"
#include "ble/ble_custom_service.hpp"

#endif

namespace Ble::Stack
{

TSoftDevicePtr createSoftDevice(
    Ble::ServiceFactory::TBleFactoryPtr&& _pServiceCreator
)
{

#if defined (USE_BLE_SERVICES)
    return Ble::Stack::createBleStackKeeper(
        std::move( _pServiceCreator )
    );
#else
    return nullptr;
#endif


}


}