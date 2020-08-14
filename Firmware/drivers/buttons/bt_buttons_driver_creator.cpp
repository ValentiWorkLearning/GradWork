#include "inc/buttons/bt_buttons_driver_creator.hpp"

#if defined (USE_DEVICE_SPECIFIC)

#include "inc/buttons/bt_nordic_hardware_backend.hpp"

#else

#include "inc/buttons/bt_win32_hardware_buttons_manual_backend.hpp"

#endif


namespace Buttons
{

TButtonsBackendPtr
createButtonsBackend()
{
#if defined (USE_DEVICE_SPECIFIC)
    return std::make_unique<NordicButtonsBackend>();
#else
    return std::make_unique<Win32ButtonsBackend>();
#endif
}

TButtonTimerWrapperPtr
createTimerBackend()
{

#if defined (USE_DEVICE_SPECIFIC)
    return std::make_unique<NordicTimerBackend>();
#else
    return std::make_unique<Win32TimerBackend>();
#endif
}


}