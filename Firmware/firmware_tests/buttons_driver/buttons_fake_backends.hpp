#pragma once

#include "ih/drivers/ih_button_driver.hpp"

namespace Buttons
{

class FakeTimerBackend
{

public:
    Simple::Signal<void()> onTimerExpired;

public:

    bool isTimerEllapsed() const
    {
        return m_isTimerEllapsed;
    };

    void startTimer()
    {
        m_isTimerEllapsed = false;
    }

    void stopTimer()
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

class FakeButtonsBackend
{

public:
    Simple::Signal<void(ButtonId, ButtonBackendEvent)> onButtonEvent;

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

}