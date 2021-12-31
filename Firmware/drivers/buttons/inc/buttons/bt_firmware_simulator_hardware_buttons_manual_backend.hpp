#pragma once

#include "ih/drivers/ih_button_driver.hpp"

#include <atomic>

namespace Buttons
{
class FirmwareSimulatorTimerBackend
{

public:
    FirmwareSimulatorTimerBackend();

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

class FirmwareSimulatorButtonsBackend
{

public:
    FirmwareSimulatorButtonsBackend();

public:
    Simple::Signal<void(ButtonId, ButtonBackendEvent)> onButtonEvent;

public:
    void initialize();
private:
    void initInternals();
};

} // namespace Buttons
