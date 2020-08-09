#include "inc/buttons/bt_buttons_driver_creator.hpp"

#if defined (USE_DEVICE_SPECIFIC)

#include "inc/buttons/bt_nordic_hardware_backend.hpp"

#endif

namespace Buttons
{

TButtonsBackendPtr
createButtonsBackend()
{
#if defined (USE_DEVICE_SPECIFIC)
    return std::make_unique<NordicButtonsBackend>();
#endif
    return nullptr;
}

TButtonTimerWrapperPtr
createTimerBackend()
{

#if defined (USE_DEVICE_SPECIFIC)
    return std::make_unique<NordicTimerBackend>();
#endif
    return nullptr;
}


}