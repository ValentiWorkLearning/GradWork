<<<<<<< HEAD:Firmware/drivers/buttons/bt_os_win32_hardware_buttons_manual_backend.cpp
#include "inc/buttons/bt_os_hardware_buttons_manual_backend.hpp"
=======
#include "inc/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.hpp"
>>>>>>> master:Firmware/drivers/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.cpp

#include <utils/CallbackConnector.hpp>
#include <utils/MetaUtils.hpp>

#ifdef WIN32

#include <Windows.h>

namespace Buttons
{

<<<<<<< HEAD:Firmware/drivers/buttons/bt_os_win32_hardware_buttons_manual_backend.cpp
OsTimerBackend::OsTimerBackend() : m_isTimerEllapsed{true}
{
}

void OsTimerBackend::startTimer()
=======
FirmwareSimulatorTimerBackend::FirmwareSimulatorTimerBackend() : m_isTimerEllapsed{true}
{
}

void FirmwareSimulatorTimerBackend::startTimer()
>>>>>>> master:Firmware/drivers/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.cpp
{
    if (!m_isTimerEllapsed)
    {
        stopTimer();
        startTimer();
    }

    auto timerEllapsedCallback = cbc::obtain_connector(
        [this](HWND, UINT, UINT_PTR, DWORD) -> VOID { onTimerExpired.emit(); });

    SetTimer(
        nullptr,
        TimerId,
        ClicksDetectionPeriodMs,
        reinterpret_cast<TIMERPROC>(timerEllapsedCallback));

    m_isTimerEllapsed = false;
}

<<<<<<< HEAD:Firmware/drivers/buttons/bt_os_win32_hardware_buttons_manual_backend.cpp
void OsTimerBackend::stopTimer()
=======
void FirmwareSimulatorTimerBackend::stopTimer()
>>>>>>> master:Firmware/drivers/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.cpp
{
    KillTimer(nullptr, TimerId);
    m_isTimerEllapsed = true;
}

<<<<<<< HEAD:Firmware/drivers/buttons/bt_os_win32_hardware_buttons_manual_backend.cpp
void OsTimerBackend::initialize()
{
}

bool OsTimerBackend::isTimerEllapsed() const
=======
void FirmwareSimulatorTimerBackend::initialize()
{
}

bool FirmwareSimulatorTimerBackend::isTimerEllapsed() const
>>>>>>> master:Firmware/drivers/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.cpp
{
    return m_isTimerEllapsed;
}

<<<<<<< HEAD:Firmware/drivers/buttons/bt_os_win32_hardware_buttons_manual_backend.cpp
OsButtonsBackend::OsButtonsBackend()
{
}

void OsButtonsBackend::initialize()
=======
FirmwareSimulatorButtonsBackend::FirmwareSimulatorButtonsBackend()
{
    initInternals();
}

void FirmwareSimulatorButtonsBackend::initInternals()
>>>>>>> master:Firmware/drivers/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.cpp
{
    HINSTANCE appInstance = GetModuleHandle(nullptr);

    auto hookKeyboardCallback =
        cbc::obtain_connector([this](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT {
            KBDLLHOOKSTRUCT* pKeyboard = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

            if (wParam == WM_KEYUP)
            {
                switch (pKeyboard->vkCode)
                {
                case VK_LEFT:
                    onButtonEvent.emit(
                        Buttons::ButtonId::kLeftButtonBottom, ButtonBackendEvent::kReleased);
                    break;
                case VK_RIGHT:
                    onButtonEvent.emit(
                        Buttons::ButtonId::kLeftButtonTop, ButtonBackendEvent::kReleased);
                    break;
                }
            }
            else if (wParam == WM_KEYDOWN)
            {
                switch (pKeyboard->vkCode)
                {
                case VK_LEFT:
                    onButtonEvent.emit(
                        Buttons::ButtonId::kLeftButtonBottom, ButtonBackendEvent::kPressed);
                    break;
                case VK_RIGHT:
                    onButtonEvent.emit(
                        Buttons::ButtonId::kLeftButtonTop, ButtonBackendEvent::kPressed);
                    break;
                }
            }
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        });

    SetWindowsHookEx(
        WH_KEYBOARD_LL, reinterpret_cast<HOOKPROC>(hookKeyboardCallback), appInstance, 0);
}

<<<<<<< HEAD:Firmware/drivers/buttons/bt_os_win32_hardware_buttons_manual_backend.cpp
=======
void FirmwareSimulatorButtonsBackend::initialize()
{
}

>>>>>>> master:Firmware/drivers/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.cpp
} // namespace Buttons

#else

namespace Buttons
{
FirmwareSimulatorTimerBackend::FirmwareSimulatorTimerBackend()
{
}

bool FirmwareSimulatorTimerBackend::isTimerEllapsed() const
{
    return false;
}


void FirmwareSimulatorTimerBackend::startTimer(){}

void FirmwareSimulatorTimerBackend::stopTimer(){}

void FirmwareSimulatorTimerBackend::initialize(){}


FirmwareSimulatorButtonsBackend::FirmwareSimulatorButtonsBackend(){}

void FirmwareSimulatorButtonsBackend::initialize(){}
void FirmwareSimulatorButtonsBackend::initInternals(){}

}
#endif
