#pragma once

#include "utils/Noncopyable.hpp"
#include "utils/SimpleSignal.hpp"
#include "utils/TimeWrapper.hpp"

#include <chrono>
#include <memory>

#include "logger/logger_service.hpp"

namespace Buttons
{

enum class ButtonState : std::uint8_t
{
    kButtonUp,
    kButtonDown,
    kButtonClick,
    kButtonDblClick,
    kButtonLongPress,
    Undefined
};

enum class ButtonId : std::uint8_t
{
    kLeftButtonTop,
    kLeftButtonMedium,
    kLeftButtonBottom,
    kRightButtonTop,
    kRightButtonBottom
};

struct ButtonEvent
{
    ButtonId buttonId;
    ButtonState buttonEvent;
};

enum class ButtonBackendEvent
{
    kPressed,
    kReleased
};

template <typename TTimerWrapper, typename TBackend> class ButtonsDriverTemplate
{

public:
    ButtonsDriverTemplate()
        : m_buttons{
              ButtonDescriptor{ButtonId::kLeftButtonTop, ButtonState::Undefined, 0, false},
              ButtonDescriptor{ButtonId::kLeftButtonMedium, ButtonState::Undefined, 0, false},
              ButtonDescriptor{ButtonId::kLeftButtonBottom, ButtonState::Undefined, 0, false},
              ButtonDescriptor{ButtonId::kRightButtonTop, ButtonState::Undefined, 0, false},
              ButtonDescriptor{ButtonId::kRightButtonBottom, ButtonState::Undefined, 0, false}}
    {
        m_timerImpl.onTimerExpired.connect([this] { handleTimerExpired(); });
        m_buttonBackendImpl.onButtonEvent.connect(
            [this](ButtonId _buttonId, ButtonBackendEvent _buttonEvent) {
                handleButtonsBackendEvent(_buttonId, _buttonEvent);
            });
    }

public:
    void initializeHalDependent() noexcept
    {
        m_timerImpl.initialize();
        m_buttonBackendImpl.initialize();
    }

public:
    Simple::Signal<void(ButtonEvent)> onButtonEvent;

public:
    TTimerWrapper* getTimeWrapper() noexcept
    {
        return &m_timerImpl;
    }

    TBackend* getButtonsBackend() noexcept
    {
        return &m_buttonBackendImpl;
    }

private:
    void handleTimerExpired() noexcept
    {
        for (auto& buttonDescriptor : m_buttons)
        {
            if (buttonDescriptor.state != ButtonState::kButtonDown)
            {
                switch (buttonDescriptor.pressCount)
                {
                case 1:
                    LOG_DEBUG(
                        "onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonClick });");
                    onButtonEvent.emit({buttonDescriptor.id, ButtonState::kButtonClick});
                    break;
                case 2:
                    LOG_DEBUG(
                        "onButtonEvent.emit({ _buttonId, ButtonState::kButtonDblClick });");
                    onButtonEvent.emit({buttonDescriptor.id, ButtonState::kButtonDblClick});
                    break;

                default:
                    break;
                }
                buttonDescriptor.pressCount = 0;
            }
            else
            {
                buttonDescriptor.longPressTimeoutExpired = true;
            }
        }
    }

    void handleButtonsBackendEvent(ButtonId _buttonId, ButtonBackendEvent _buttonEvent) noexcept
    {
        using TButtonUnderlying = std::underlying_type_t<ButtonId>;
        auto arrayIndex = static_cast<TButtonUnderlying>(_buttonId);

        if (_buttonEvent == ButtonBackendEvent::kPressed)
        {
            m_buttons[arrayIndex].state = ButtonState::kButtonDown;
            onButtonEvent.emit({_buttonId, ButtonState::kButtonDown});

            m_buttons[arrayIndex].pressCount = m_buttons[arrayIndex].pressCount + 1;

            if (m_timerImpl.isTimerEllapsed())
                m_timerImpl.startTimer();
        }
        else if (_buttonEvent == ButtonBackendEvent::kReleased)
        {
            m_buttons[arrayIndex].state = ButtonState::kButtonUp;
            onButtonEvent.emit({_buttonId, ButtonState::kButtonUp});

            if (m_buttons[arrayIndex].longPressTimeoutExpired)
            {
                m_buttons[arrayIndex].pressCount = 0;
                m_buttons[arrayIndex].longPressTimeoutExpired = false;
                LOG_DEBUG(
                    "onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonLongPress });");
                onButtonEvent.emit({m_buttons[arrayIndex].id, ButtonState::kButtonLongPress});
            }
        }
    }

private:
    struct ButtonDescriptor
    {
        ButtonId id;
        ButtonState state;
        std::uint8_t pressCount;
        bool longPressTimeoutExpired;
    };

    static constexpr std::uint8_t ButtonsCount = 5;
    using ButtonsCollection = std::array<ButtonDescriptor, ButtonsCount>;

    ButtonsCollection m_buttons;

    TTimerWrapper m_timerImpl;
    TBackend m_buttonBackendImpl;
};

} // namespace Buttons