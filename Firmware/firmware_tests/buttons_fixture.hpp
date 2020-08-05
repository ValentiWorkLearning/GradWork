#pragma once
#include <gtest/gtest.h>

#include "ih/drivers/ih_button_driver.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_ievent_handler.hpp"

#include "buttons/bt_buttons_driver.hpp"

#include "gs_event_dispatcher.hpp"

#include "buttons_fake_event_handler.hpp"
#include "buttons_fake_backends.hpp"

#include <memory>

class ButtonsDriverTest
	: public ::testing::Test
{

protected:

	void SetUp() override
	{
		m_pButtonsDriver = Buttons::createButtonsDriver();
		m_pFakeTimer = Buttons::createFakeTimerBackend();
		m_pFakeButtonsBackend = Buttons::createFakeButtonsBackend();

		m_pButtonsDriver->setButtonsBackend( m_pFakeButtonsBackend.get() );
		m_pButtonsDriver->setTimer( m_pFakeTimer.get() );

		m_pEventDispatcher = Graphics::Events::createEventDispatcher();
		m_pFakeEventHandler = FakeButton::createFakeButtonsHandler();

		m_pEventDispatcher->subscribe(
				Graphics::Events::EventGroup::Buttons
			,	[this](const Graphics::Events::TEvent& _event)
			{
				m_pFakeEventHandler->handleEvent( _event );
			}
		);

		m_pButtonsDriver->onButtonEvent.connect(
			[this]( const Buttons::ButtonEvent& _buttonEvent )
			{
				m_pEventDispatcher->postEvent(
					{
							Graphics::Events::EventGroup::Buttons
						,	toUiEvent( _buttonEvent.buttonEvent )
						,	_buttonEvent.buttonId
					}
				);
			}
		);
	}

protected:

	Buttons::TButtonsDriverPtr m_pButtonsDriver;
	Buttons::TFakeTimerBackendPtr m_pFakeTimer;
	Buttons::TFakeButtonsBackendPtr m_pFakeButtonsBackend;

	Graphics::Events::TEventDispatcherPtr m_pEventDispatcher;

	FakeButton::TFakeButtonsHandlerPtr m_pFakeEventHandler;
private:

	Graphics::Events::TButtonsEvents toUiEvent( Buttons::ButtonState _state )
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