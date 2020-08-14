#pragma once

#include "ih/drivers/ih_button_driver.hpp"

namespace Buttons
{

class FakeTimerBackend
    :   public IButtonTimerWrapper
{

public:

    virtual ~FakeTimerBackend() = default;

public:

    bool isTimerEllapsed() const
    {
        return m_isTimerEllapsed;
    };

    void startTimer() override
    {
        m_isTimerEllapsed = false;
    }

    void stopTimer() override
    {
        m_isTimerEllapsed = true;
    }

public:

    void ellapseTimer()
    {
        m_isTimerEllapsed = true;
        onTimerExpired.emit();
    }

private:

    bool m_isTimerEllapsed = false;
};

using TFakeTimerBackendPtr = std::unique_ptr<FakeTimerBackend>;

TFakeTimerBackendPtr createFakeTimerBackend()
{
    return std::make_unique<FakeTimerBackend>();
}

class FakeButtonsBackend
    :   public IButtonsBackend
{

public:

    virtual ~FakeButtonsBackend() = default;

public:

    void fakeButtonPress( ButtonId _buttonId )
    {
        onButtonEvent.emit(_buttonId, ButtonBackendEvent::kPressed );
    }
    void fakeButtonRelease( ButtonId _buttonId )
    {
        onButtonEvent.emit(_buttonId, ButtonBackendEvent::kReleased );
    }
};

using TFakeButtonsBackendPtr = std::unique_ptr<FakeButtonsBackend>;

TFakeButtonsBackendPtr createFakeButtonsBackend()
{
    return std::make_unique<FakeButtonsBackend>();
}

}