#pragma once
#include <gtest/gtest.h>

#include "ih/drivers/ih_button_driver.hpp"

#include "ih/gs_events.hpp"
#include "ih/gs_ievent_handler.hpp"

#include "gs_event_dispatcher.hpp"

#include "buttons_fake_event_handler.hpp"

#include <memory>

class ButtonsDriverTest
	: public ::testing::Test
{

protected:

	void SetUp() override
	{
	
		//m_pButtonsDriver = Buttons::createButtonsDriver();
		m_pEventDispatcher = Graphics::Events::createEventDispatcher();
		m_pFakeEventHandler = FakeButton::createFakeButtonsHandler();

		m_pEventDispatcher->subscribe(
				Graphics::Events::EventGroup::Buttons
			,	[this](const Graphics::Events::TEvent& _event)
			{
				m_pFakeEventHandler->handleEvent( _event );
			}
		);
	}

	
	
protected:

	Buttons::TButtonsDriverPtr m_pButtonsDriver;
	Graphics::Events::TEventDispatcherPtr m_pEventDispatcher;
	FakeButton::TFakeButtonsHandlerPtr m_pFakeEventHandler;

private:

};