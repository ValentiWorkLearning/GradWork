#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ih/drivers/ih_button_driver.hpp"

#include "buttons_fixture.hpp"

TEST_F(ButtonsDriverTest, SingleClick)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked
	};

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(0);
	m_pFakeButtonsBackend->fakeButtonRelease(0);
	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ( m_pFakeEventHandler->getEventsCount(), EventsCount );
	
	for (size_t i{}; i< EventsCount; ++i )
		ASSERT_EQ( m_pFakeEventHandler->getEventAt(i), eventsToCheck[i] );

	ASSERT_EQ( m_pFakeEventHandler->getLastButton(), 0 );

}

TEST_F(ButtonsDriverTest, DoubleClickWithoutTimeout )
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked
		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonDblClick
	};

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(0);
	m_pFakeButtonsBackend->fakeButtonRelease(0);

	m_pFakeButtonsBackend->fakeButtonPress(0);
	m_pFakeButtonsBackend->fakeButtonRelease(0);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), 0);

}


TEST_F(ButtonsDriverTest, TwoSeparateClicksBecauseOfTimeoutBetweenClick )
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked
		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked
	};

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(0);
	m_pFakeButtonsBackend->fakeButtonRelease(0);

	m_pFakeTimer->ellapseTimer();

	m_pFakeButtonsBackend->fakeButtonPress(0);
	m_pFakeButtonsBackend->fakeButtonRelease(0);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), 0);

}