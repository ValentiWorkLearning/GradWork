#pragma once

#include "ih/drivers/ih_button_driver.hpp"

#include <atomic>

namespace Buttons
{

class Win32TimerBackend
{

public:
    Win32TimerBackend();

public:
    Simple::Signal<void()> onTimerExpired;

public:
    bool isTimerEllapsed() const;

    void startTimer();

    void stopTimer();

    void initialize();

private:
    static constexpr inline std::uint32_t ClicksDetectionPeriodMs = 400;
    static constexpr inline std::uint32_t TimerId = 128;
    std::atomic<bool> m_isTimerEllapsed = false;
};

class Win32ButtonsBackend
{

public:
    Win32ButtonsBackend();

public:
    Simple::Signal<void(ButtonId, ButtonBackendEvent)> onButtonEvent;

public:
    void initialize();

private:
    void initWin32ApiHook();
};

} // namespace Buttons