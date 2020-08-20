#pragma once

#include "ih/drivers/ih_button_driver.hpp"

#include <atomic>

namespace Buttons
{

class Win32TimerBackend
    :   public IButtonTimerWrapper
{

public:

    Win32TimerBackend();

    virtual ~Win32TimerBackend() = default;

public:

    bool isTimerEllapsed() const override;

    void startTimer() override;

    void stopTimer() override;

private:
    static constexpr inline std::uint32_t ClicksDetectionPeriodMs = 400;
    static constexpr std::uint32_t TimerId = 128;
    std::atomic<bool> m_isTimerEllapsed = false;
};

class Win32ButtonsBackend
    :   public IButtonsBackend
{

public:

    Win32ButtonsBackend();

    virtual ~Win32ButtonsBackend() = default;

private:

    void initWin32ApiHook();
};



}