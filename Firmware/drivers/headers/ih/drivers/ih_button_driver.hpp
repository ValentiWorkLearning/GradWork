#pragma once

#include "utils/Noncopyable.hpp"
#include "utils/TimeWrapper.hpp"
#include "utils/SimpleSignal.hpp"

#include <memory>
#include <chrono>

namespace Buttons
{

enum class ButtonState
{
        kButtonUp
    ,   kButtonDown
    ,   kButtonClick
    ,   kButtonDblClick
    ,   kButtonLongPress
    ,   Undefined
};


enum class ButtonId
{
        kLeftButtonTop
    ,   kLeftButtonMedium
    ,   kLeftButtonBottom
    ,   kRightButtonTop
    ,   kRightButtonBottom
};

struct ButtonEvent
{
    ButtonId buttonId;
    ButtonState buttonEvent;
};

class IButtonTimerWrapper
{

public:

    virtual ~IButtonTimerWrapper() = default;

    virtual void startTimer() = 0;

    virtual void stopTimer() = 0;

    virtual bool isTimerEllapsed()const = 0;

public:
    Simple::Signal<void()> onTimerExpired;
};

using TButtonTimerWrapperPtr = std::unique_ptr<IButtonTimerWrapper>;

enum class ButtonBackendEvent
{
        kPressed
    ,   kReleased
};

class IButtonsBackend
{

public:

    virtual ~IButtonsBackend() = default;

public:

public:
    Simple::Signal<void( ButtonId, ButtonBackendEvent)> onButtonEvent;
};

using TButtonsBackendPtr = std::unique_ptr<IButtonsBackend>;

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

}