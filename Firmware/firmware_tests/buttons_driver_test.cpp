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

	constexpr std::uint8_t TestButtonId = 0;

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);
	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ( m_pFakeEventHandler->getEventsCount(), EventsCount );
	
	for (size_t i{}; i< EventsCount; ++i )
		ASSERT_EQ( m_pFakeEventHandler->getEventAt(i), eventsToCheck[i] );

	ASSERT_EQ( m_pFakeEventHandler->getLastButton(), TestButtonId);

}

TEST_F(ButtonsDriverTest, SingleClickDifferentButtons)
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

	constexpr std::uint8_t TestButtonId = 0;
	constexpr std::uint8_t TestSecondButtonId = 1;

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestSecondButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestSecondButtonId);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestSecondButtonId);

}

TEST_F(ButtonsDriverTest, SingleClickSequenceOfPushRelease)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonPressed

		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked

		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked
	};

	/*---------------TestingAction-------*/

	constexpr std::uint8_t TestButtonId = 0;
	constexpr std::uint8_t TestSecondButtonId = 1;

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonPress(TestSecondButtonId);

	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestSecondButtonId);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestSecondButtonId);

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

	constexpr std::uint8_t TestButtonId = 0;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestButtonId);

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

	constexpr std::uint8_t TestButtonId = 0;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeTimer->ellapseTimer();

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestButtonId);

}


TEST_F(ButtonsDriverTest, TwoSeparateClicksBecauseOfInterruptedDoubleClickSequence )
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

	constexpr std::uint8_t TestButtonId = 0;
	constexpr std::uint8_t SecondTestButtonId = 1;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(SecondTestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(SecondTestButtonId);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), SecondTestButtonId);
}

TEST_F(ButtonsDriverTest, DetectLongClickEllapsedTimer)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonLongClick
	};

	constexpr std::uint8_t TestButtonId = 0;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeTimer->ellapseTimer();
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestButtonId);
}

TEST_F(ButtonsDriverTest, DetectSequenceOfLongClicks)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonLongClick

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonLongClick
	};

	constexpr std::uint8_t TestButtonId = 0;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeTimer->ellapseTimer();
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeTimer->ellapseTimer();
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestButtonId);
}