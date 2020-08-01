#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "ih/drivers/ih_button_driver.hpp"

#include "buttons_fixture.hpp"

TEST_F(ButtonsDriverTest, SimpleSingleClick)
{
	/*---------------Setup---------------*/



	ASSERT_EQ( m_pFakeEventHandler->getLastEvent(),Graphics::Events::TButtonsEvents::ButtonReleased );

	/*---------------TestingAction-------*/

}
