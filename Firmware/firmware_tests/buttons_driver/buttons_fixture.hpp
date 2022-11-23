#pragma once
#include <gtest/gtest.h>

#include "ih/drivers/ih_button_driver.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_ievent_handler.hpp"

#include "gs_event_dispatcher.hpp"

#include "buttons_fake_backends.hpp"
#include "buttons_fake_event_handler.hpp"

#include <memory>

using TFakeTimerBackend = Buttons::FakeTimerBackend;
using TFakeButtonsBackend = Buttons::FakeButtonsBackend;
using TButtonDriver = Buttons::ButtonsDriverTemplate<TFakeTimerBackend, TFakeButtonsBackend>;

class ButtonsDriverTest : public ::testing::Test
{

protected:
    void SetUp() override
    {

        m_pEventDispatcher = Graphics::Events::createEventDispatcher();
        m_pFakeEventHandler = FakeButton::createFakeButtonsHandler();

        m_pFakeTimer = m_pButtonsDriver.getTimeWrapper();
        m_pFakeButtonsBackend = m_pButtonsDriver.getButtonsBackend();

        m_pFakeEventHandler->initSubscriptions(*m_pEventDispatcher);

        m_pButtonsDriver.onButtonEvent.connect([this](const Buttons::ButtonEvent& _buttonEvent) {
            m_pEventDispatcher->postEvent(
                {Graphics::Events::EventGroup::Buttons,
                 toUiEvent(_buttonEvent.buttonEvent),
                 _buttonEvent.buttonId});
        });
    }

protected:
    TButtonDriver m_pButtonsDriver;
    TFakeTimerBackend* m_pFakeTimer{nullptr};
    TFakeButtonsBackend* m_pFakeButtonsBackend{nullptr};

    Graphics::Events::TEventDispatcherPtr m_pEventDispatcher;

    FakeButton::TFakeButtonsHandlerPtr m_pFakeEventHandler;

private:
    Graphics::Events::TButtonsEvents toUiEvent(Buttons::ButtonState _state)
    {
        using BtGuiEvent = Graphics::Events::TButtonsEvents;
        switch (_state)
        {
        case Buttons::ButtonState::kButtonUp:
            return BtGuiEvent::ButtonReleased;
            break;
        case Buttons::ButtonState::kButtonDown:
            return BtGuiEvent::ButtonPressed;
            break;
        case Buttons::ButtonState::kButtonClick:
            return BtGuiEvent::ButtonClicked;
            break;
        case Buttons::ButtonState::kButtonDblClick:
            return BtGuiEvent::ButtonDblClick;
            break;
        case Buttons::ButtonState::kButtonLongPress:
            return BtGuiEvent::ButtonLongClick;
            break;
        default:
            break;
        }

        assert(false);
        return BtGuiEvent::ButtonReleased;
    }
};