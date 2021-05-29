#pragma once

#include "ih/drivers/ih_button_driver.hpp"

#include <atomic>

namespace Buttons
{

class NordicTimerBackend
{

public:
    Simple::Signal<void()> onTimerExpired;

public:
    bool isTimerEllapsed() const;

    void startTimer();

    void stopTimer();

    void initialize();

private:
    static std::uint32_t convertToTimerTicks(std::chrono::milliseconds _interval);

private:
    const std::chrono::milliseconds m_buttonLongPressDetectionDelay
        = std::chrono::milliseconds{400};

    std::atomic<bool> m_isTimerEllapsed = false;
    std::atomic<bool> m_isInitialized = false;
};

class NordicButtonsBackend
{

public:
    void initialize();

public:
    Simple::Signal<void(ButtonId, ButtonBackendEvent)> onButtonEvent;

private:
    void initNordicButtonsBackend();

    void handleHardwareButtonEvent(std::uint8_t _pinNumber, std::uint8_t _buttonEvent);
};

} // namespace Buttons