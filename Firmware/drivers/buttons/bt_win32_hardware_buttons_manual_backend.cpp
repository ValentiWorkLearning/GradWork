#include "inc/buttons/bt_win32_hardware_buttons_manual_backend.hpp"

#include "utils/CallbackConnector.hpp"
#include "utils/MetaUtils.hpp"

#include <Windows.h>

namespace Buttons
{

Win32TimerBackend::Win32TimerBackend()
{
}

void
Win32TimerBackend::startTimer()
{

    if (!m_isTimerEllapsed)
    {
        stopTimer();
        startTimer();
    }

    m_isTimerEllapsed = false;
}

void
Win32TimerBackend::stopTimer()
{
    m_isTimerEllapsed = true;
}

bool
Win32TimerBackend::isTimerEllapsed() const
{
    return m_isTimerEllapsed;
}

Win32ButtonsBackend::Win32ButtonsBackend()
{
    initWin32ApiHook();
}

void
Win32ButtonsBackend::initWin32ApiHook()
{
    HINSTANCE appInstance = GetModuleHandle(nullptr);

    auto hookKeyboardCallback = cbc::obtain_connector(
        [this](int nCode, WPARAM wParam, LPARAM lParam)->LRESULT
        {
            KBDLLHOOKSTRUCT* pKeyboard = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);

            if (wParam == WM_KEYUP) {
                switch (pKeyboard->vkCode)
                {
                case VK_LEFT:
                    onButtonEvent.emit(Buttons::ButtonId::kLeftButtonBottom, ButtonBackendEvent::kReleased);
                    break;
                case VK_RIGHT:
                    onButtonEvent.emit(Buttons::ButtonId::kLeftButtonTop, ButtonBackendEvent::kReleased);
                    break;
                }
            }
            else if (wParam == WM_KEYDOWN) {
                switch (pKeyboard->vkCode)
                {
                case VK_LEFT:
                    onButtonEvent.emit(Buttons::ButtonId::kLeftButtonBottom, ButtonBackendEvent::kPressed);
                    break;
                case VK_RIGHT:
                    onButtonEvent.emit(Buttons::ButtonId::kLeftButtonTop, ButtonBackendEvent::kPressed);
                    break;
                }
            }
            return CallNextHookEx(NULL, nCode, wParam, lParam);
        }
   );

    SetWindowsHookEx(WH_KEYBOARD_LL, hookKeyboardCallback, appInstance, 0);
}
}
