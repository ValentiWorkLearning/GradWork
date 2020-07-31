#pragma once

#include "utils/Noncopyable.hpp"
#include "utils/TimeWrapper.hpp"
#include "utils/SimpleSignal.hpp"

#include <memory>

namespace Buttons
{

enum class Event
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
    Event buttonEvent;
};

class IButtonTimerWrapper
{

public:

    virtual ~IButtonTimerWrapper() = default;

public:
    Simple::Signal<void()> onTimerExpired;
};

using TTimerWrapperPtr = std::unique_ptr<IButtonTimerWrapper>;


class IButtonsDriver
{

public:

    virtual ~IButtonsDriver() = default;

public:

    virtual void setTimer( TTimerWrapperPtr&& _pTimerWrapper ) = 0;

public:

    Simple::Signal<void(ButtonEvent)> onButtonEvent;

};

using TButtonsDriverPtr = std::unique_ptr<IButtonsDriver>;

//TButtonsDriverPtr createButtonsDriver();

}