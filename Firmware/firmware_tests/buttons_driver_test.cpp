#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ih/drivers/ih_button_driver.hpp"

#include "buttons_fixture.hpp"

TEST_F(ButtonsDriverTest, SimpleSingleClick)
{
	/*---------------Setup---------------*/


	const auto eventsToCheck = std::array{
			Graphics::Events::TButtonsEvents::ButtonPressed
		,	Graphics::Events::TButtonsEvents::ButtonReleased
		,	Graphics::Events::TButtonsEvents::ButtonClicked
	};

	constexpr size_t EventsCount = 3;
	ASSERT_EQ( m_pFakeEventHandler->getEventsCount(), EventsCount );
	
	for (size_t i{}; i< EventsCount; ++i )
		ASSERT_EQ( m_pFakeEventHandler->getEventAt(i), eventsToCheck[i] );

	/*---------------TestingAction-------*/

}
