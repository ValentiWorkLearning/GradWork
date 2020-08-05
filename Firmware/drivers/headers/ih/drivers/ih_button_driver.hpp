#pragma once

#include "utils/Noncopyable.hpp"
#include "utils/TimeWrapper.hpp"
#include "utils/SimpleSignal.hpp"

#include <memory>

namespace Buttons
{

enum class ButtonState
{
        kButtonUp
    ,   kButtonDown
    ,   kButtonClick
    ,   kButtonDblClick
    ,   kButtonLongPress
};


struct ButtonEvent
{
    std::uint8_t buttonId;
    ButtonState buttonEvent;
};

class IButtonTimerWrapper
{

public:

    virtual ~IButtonTimerWrapper() = default;

public:
    Simple::Signal<void()> onTimerExpired;
};

enum class ButtonBackendEvent
{
        Pressed
    ,   Released
};

class IButtonsBackend
{

public:

    virtual ~IButtonsBackend() = default;

public:

public:
    Simple::Signal<void( std::uint8_t, ButtonBackendEvent)> onButtonEvent;
};

class IButtonsDriver
{

public:

    virtual ~IButtonsDriver() = default;

public:

    virtual void setTimer( IButtonTimerWrapper* _pTimerWrapper ) = 0;

    virtual void setButtonsBackend( IButtonsBackend* _pTimerWrapper ) = 0;

public:

    Simple::Signal<void(ButtonEvent)> onButtonEvent;
};

using TButtonsDriverPtr = std::unique_ptr<IButtonsDriver>;

//TButtonsDriverPtr createButtonsDriver();

}