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

    void ellapseTimer()
    {
        onTimerExpired.emit();
    }

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

    void fakeButtonPress( std::uint8_t _buttonId )
    {
        onButtonEvent.emit(_buttonId, ButtonBackendEvent::Pressed );
    }
    void fakeButtonRelease( std::uint8_t _buttonId )
    {
        onButtonEvent.emit(_buttonId, ButtonBackendEvent::Released );
    }
};

using TFakeButtonsBackendPtr = std::unique_ptr<FakeButtonsBackend>;

TFakeButtonsBackendPtr createFakeButtonsBackend()
{
    return std::make_unique<FakeButtonsBackend>();
}

}