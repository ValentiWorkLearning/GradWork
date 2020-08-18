#pragma once

#include "ih/drivers/ih_button_driver.hpp"

#include <atomic>

namespace Buttons
{

class NordicTimerBackend
    :   public IButtonTimerWrapper
{

public:

    NordicTimerBackend();

    virtual ~NordicTimerBackend() = default;

public:

    bool isTimerEllapsed() const override;

    void startTimer() override;

    void stopTimer() override;

private:

    std::uint32_t convertToTimerTicks( std::chrono::milliseconds _interval );

private:
    const std::chrono::milliseconds m_buttonLongPressDetectionDelay = std::chrono::milliseconds{400};

    std::atomic<bool> m_isTimerEllapsed = false;
};

class NordicButtonsBackend
    :   public IButtonsBackend
{

public:

    NordicButtonsBackend();

    virtual ~NordicButtonsBackend() = default;

private:

    void initNordicButtonsBackend();

    void handleHardwareButtonEvent( std::uint8_t _pinNumber, std::uint8_t _buttonEvent );
};



}