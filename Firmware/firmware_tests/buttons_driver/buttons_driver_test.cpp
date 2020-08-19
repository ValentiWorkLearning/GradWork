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

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);
	m_pFakeTimer->ellapseTimer();

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

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased

		,	Graphics::Events::TButtonsEvents::ButtonClicked
		,	Graphics::Events::TButtonsEvents::ButtonClicked
	};

	/*---------------TestingAction-------*/

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;
	constexpr Buttons::ButtonId TestSecondButtonId = Buttons::ButtonId::kLeftButtonMedium;

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestSecondButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestSecondButtonId);

	m_pFakeTimer->ellapseTimer();

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
		,	Graphics::Events::TButtonsEvents::ButtonReleased

		,	Graphics::Events::TButtonsEvents::ButtonClicked
		,	Graphics::Events::TButtonsEvents::ButtonClicked
	};

	/*---------------TestingAction-------*/

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;
	constexpr Buttons::ButtonId TestSecondButtonId = Buttons::ButtonId::kLeftButtonMedium;

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonPress(TestSecondButtonId);

	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestSecondButtonId);

	m_pFakeTimer->ellapseTimer();

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

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonDblClick
	};

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeTimer->ellapseTimer();

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestButtonId);

}


TEST_F(ButtonsDriverTest, ThreeSeparateClicksBecauseOfTimeoutBetweenClick )
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked

	};

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeTimer->ellapseTimer();

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeTimer->ellapseTimer();

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeTimer->ellapseTimer();

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

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;
	constexpr Buttons::ButtonId TestSecondButtonId = Buttons::ButtonId::kLeftButtonMedium;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeTimer->ellapseTimer();

	m_pFakeButtonsBackend->fakeButtonPress(TestSecondButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestSecondButtonId);

	m_pFakeTimer->ellapseTimer();

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestSecondButtonId);
}

TEST_F(ButtonsDriverTest, DetectLongClickEllapsedTimer)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonLongClick
	};

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;

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

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;

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


TEST_F(ButtonsDriverTest, DetectSequenceOfDoubleClicks)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonDblClick

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonDblClick
	};

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeTimer->ellapseTimer();

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);
	m_pFakeTimer->ellapseTimer();

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestButtonId);
}


TEST_F(ButtonsDriverTest, DetectButtonClickAfterLongClick)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonLongClick

		,	Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked
	};

	constexpr Buttons::ButtonId TestButtonId = Buttons::ButtonId::kLeftButtonTop;

	/*---------------TestingAction-------*/

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeTimer->ellapseTimer();
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);

	m_pFakeButtonsBackend->fakeButtonPress(TestButtonId);
	m_pFakeButtonsBackend->fakeButtonRelease(TestButtonId);
	m_pFakeTimer->ellapseTimer();

	m_pEventDispatcher->processEventQueue();

	/*---------------Assertions---------------*/

	constexpr size_t EventsCount = eventsToCheck.size();
	ASSERT_EQ(m_pFakeEventHandler->getEventsCount(), EventsCount);

	for (size_t i{}; i < EventsCount; ++i)
		ASSERT_EQ(m_pFakeEventHandler->getEventAt(i), eventsToCheck[i]);

	ASSERT_EQ(m_pFakeEventHandler->getLastButton(), TestButtonId);
}