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

    static constexpr inline std::uint32_t ClicksDetectionPeriodMs = 100;

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
};



}