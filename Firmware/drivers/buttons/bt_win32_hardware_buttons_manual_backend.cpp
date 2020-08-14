#include "inc/buttons/bt_win32_hardware_buttons_manual_backend.hpp"

#include "utils/CallbackConnector.hpp"
#include "utils/MetaUtils.hpp"

#include <Windows.h>

namespace {
    LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
    {
        KBDLLHOOKSTRUCT* pKeyboard = reinterpret_cast<KBDLLHOOKSTRUCT*>( lParam );

        if (wParam == WM_KEYUP) {
            switch (pKeyboard->vkCode)
            {
            case VK_SPACE:
                
                break;
            }
        }
        return CallNextHookEx(NULL, nCode, wParam, lParam);;
    }
}


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
    HINSTANCE appInstance = GetModuleHandle(NULL);
    SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, appInstance, 0);
}
}
