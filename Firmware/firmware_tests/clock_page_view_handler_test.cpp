#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "clock_watch_fake_view.hpp"
#include "widgets_layer/pages/clock_page/gs_clock_page_handler.hpp"

TEST( ClockPageHandlerTest, CanSetupMock )
{
	FakeClockPage fakeView;
	auto pageWatchHandler = Graphics::Views::createPageWatchHandler( &fakeView );

	EXPECT_CALL(fakeView, setHours("00"))
		.Times(0);
	pageWatchHandler->handleEvent(
			{
					Graphics::Events::EventGroup::DateTime
				,	Graphics::Events::TDateTimeEvents::DateTimeChanged
				,	TimeWrapper("1971/01/9 13:24:43", '/', ':')
			}
	);
}

TEST( ClockPageHandlerTest, PageLabelsArentUpdateByHandlerWhenPageHidden )
{
	using ::testing::Return;

	FakeClockPage fakeView;
	auto pageWatchHandler = Graphics::Views::createPageWatchHandler( &fakeView );

	EXPECT_CALL(fakeView, isVisible())
		.Times( 1 )
		.WillOnce( Return( false ) );

	EXPECT_CALL( fakeView, setHours( "00" ) )
		.Times( 0 );

	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper( "1971/01/9 13:24:43", '/', ':' )
		}
	);
}


TEST( ClockPageHandlerTest, AllPageLabelsRefreshedWhenPageVisible )
{
	using ::testing::Return;

	FakeClockPage fakeView;
	auto pageWatchHandler = Graphics::Views::createPageWatchHandler( &fakeView );

	EXPECT_CALL( fakeView, isVisible() )
		.Times(1)
		.WillOnce( Return( true ) );

	EXPECT_CALL( fakeView, setHours( "13" ) )
		.Times(1);
	EXPECT_CALL( fakeView, setMinutes( "24" ) )
		.Times(1);
	EXPECT_CALL( fakeView, setSeconds( "43" ) )
		.Times(1);
	EXPECT_CALL( fakeView, setWeekday( std::string_view( "SUN" ) ) )
		.Times(1);
	EXPECT_CALL( fakeView, setFullDate( "JAN/9/1971" ) )
		.Times(1);

	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper( "1971/01/9 13:24:43", '/', ':' )
		}
	);
}


TEST( ClockPageHandlerTest, OnlyHoursLabelRefreshedWhenHoursChanged)
{
	using ::testing::Return;

	FakeClockPage fakeView;
	auto pageWatchHandler = Graphics::Views::createPageWatchHandler( &fakeView );

	EXPECT_CALL(fakeView, isVisible())
		.Times(2)
		.WillRepeatedly(Return(true));

	EXPECT_CALL(fakeView, setHours("13"))
		.Times(1);

	EXPECT_CALL(fakeView, setFullDate("JAN/9/1971"))
		.Times(1);
	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper( "1971/01/9 13:24:43", '/', ':' )
		}
	);

	EXPECT_CALL(fakeView, setHours("14"))
		.Times(1);
	EXPECT_CALL(fakeView, setMinutes("14"))
		.Times(0);

	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper( "1971/01/9 14:24:43", '/', ':' )
		}
	);
}

TEST(ClockPageHandlerTest, ShouldAddplyNewDateConditios)
{
	using ::testing::Return;
	using ::testing::AllOf;
	using ::testing::Args;
	using ::testing::Lt;

	FakeClockPage fakeView;
	auto pageWatchHandler = Graphics::Views::createPageWatchHandler(&fakeView);

	EXPECT_CALL(fakeView, isVisible())
		.Times(5)
		.WillRepeatedly(Return(true));

	EXPECT_CALL(fakeView, setFullDate("JAN/9/1971"))
		.Times(1);
	EXPECT_CALL(fakeView, setFullDate("FEB/10/1971"))
		.Times(1);
	EXPECT_CALL(fakeView, setFullDate("FEB/10/1972"))
		.Times(1);

	//Initial date
	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper("1971/01/9 13:24:43", '/', ':')
		}
	);

	//Weekday was changed
	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper("1971/01/10 14:24:43", '/', ':')
		}
	);

	//Month was changed
	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper("1971/02/10 14:24:43", '/', ':')
		}
	);

	//Year was changed
	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper("1972/02/10 14:24:43", '/', ':')
		}
	);
	// Just hours were chanaged, nothing to update in date
	pageWatchHandler->handleEvent(
		{
				Graphics::Events::EventGroup::DateTime
			,	Graphics::Events::TDateTimeEvents::DateTimeChanged
			,	TimeWrapper("1972/02/10 18:24:43", '/', ':')
		}
	);
}