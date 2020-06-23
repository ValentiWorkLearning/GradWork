#pragma once
#include <gtest/gtest.h>

#include "widgets_layer/pages/clock_page/gs_clock_page_handler.hpp"

#include "clock_watch_fake_view.hpp"

#include <memory>

class ClockPageHandlerTest
	: public ::testing::Test
{

protected:

	void SetUp() override
	{
		pageWatchHandler = Graphics::Views::createPageWatchHandler( &fakeView );
		pageMockWatchHandler = Graphics::Views::createPageWatchHandler( &fakePageMock );
	}

	void setDefaultDate()
	{
		using ::testing::Return;

		EXPECT_CALL(fakeView, isVisible())
			.Times(1).WillOnce(Return(true));

		pageWatchHandler->handleEvent(
			{
					Graphics::Events::EventGroup::DateTime
				,	Graphics::Events::TDateTimeEvents::DateTimeChanged
				,	TimeWrapper("2020/06/22 14:24:43", '/', ':')
			}
		);

	}

	void setupMock()
	{
		using ::testing::Return;

		EXPECT_CALL(fakePageMock, isVisible())
			.Times(1).WillOnce(Return(true));

		EXPECT_CALL( fakePageMock, setHours( "15" ) )
			.Times(1);
		EXPECT_CALL( fakePageMock, setMinutes( "24" ) )
			.Times(1);
		EXPECT_CALL( fakePageMock, setSeconds( "43" ) )
			.Times(1);
		EXPECT_CALL( fakePageMock, setWeekday( std::string_view( "MON" ) ) )
			.Times(1);
		EXPECT_CALL( fakePageMock, setFullDate( "JUN/22/2020" ) )
			.Times(1);

		pageMockWatchHandler->handleEvent(
			{
					Graphics::Events::EventGroup::DateTime
				,	Graphics::Events::TDateTimeEvents::DateTimeChanged
				,	TimeWrapper("2020/06/22 14:24:43", '/', ':')
			}
		);
	}

protected:

	FakeClockPageMock fakePageMock;
	FakeClockPage fakeView;
	std::unique_ptr<Graphics::IEventHandler> pageWatchHandler;
	std::unique_ptr<Graphics::IEventHandler> pageMockWatchHandler;
};