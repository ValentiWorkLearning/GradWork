#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "clock_page_handler_fixture.hpp"
#include "clock_watch_fake_view.hpp"

#include "widgets_layer/pages/clock_page/gs_clock_page_handler.hpp"

TEST_F(ClockPageHandlerTest, ExpectInitalValuesAfterCreation)
{
    EXPECT_EQ(fakeView.getHours(), "00");
    EXPECT_EQ(fakeView.getMinutes(), "00");
    EXPECT_EQ(fakeView.getSeconds(), ":00");
    EXPECT_EQ(fakeView.getWeekday(), ".........");
    EXPECT_EQ(fakeView.getFullDate(), "../../....");
}

TEST_F(ClockPageHandlerTest, ExpectInitialDefeaultDate)
{
    setDefaultDate();

    EXPECT_EQ(fakeView.getHours(), "14");
    EXPECT_EQ(fakeView.getMinutes(), "24");
    EXPECT_EQ(fakeView.getSeconds(), "43");
    EXPECT_EQ(fakeView.getWeekday(), "MON");
    EXPECT_EQ(fakeView.getFullDate(), "JUN/22/2020");
}

TEST_F(ClockPageHandlerTest, ViewStaysUnchangedWhenInviisible)
{
    setDefaultDate();

    using ::testing::Return;

    // Only hours were changed
    pageWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/22 14:24:43", '/', ':')});
    EXPECT_EQ(fakeView.getHours(), "14");
}

TEST_F(ClockPageHandlerTest, OnlyHoursLabelIsRefreshedWhenNewDateTimeEventOccurs)
{
    setupMock();

    using ::testing::Return;

    EXPECT_CALL(fakePageMock, isVisible()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(fakePageMock, setHours("15")).Times(1);

    // Only hours were changed
    pageMockWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/22 15:24:43", '/', ':')});
}

TEST_F(ClockPageHandlerTest, FulldateRefreshedWhenWeekdayWasChanged)
{
    setupMock();

    using ::testing::Return;

    EXPECT_CALL(fakePageMock, isVisible()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(fakePageMock, setFullDate("JUN/29/2020")).Times(1);

    // Only weekday was changed
    pageMockWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/29 14:24:43", '/', ':')});
}

TEST_F(ClockPageHandlerTest, FulldateRefreshedWhenMonthWasChanged)
{
    setupMock();

    using ::testing::Return;

    EXPECT_CALL(fakePageMock, isVisible()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(fakePageMock, setFullDate("JUL/13/2020")).Times(1);

    // Only month was changed
    pageMockWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/07/13 14:24:43", '/', ':')});
}

TEST_F(ClockPageHandlerTest, FulldateRefreshedWhenYearWasChanged)
{
    setupMock();

    using ::testing::Return;

    EXPECT_CALL(fakePageMock, isVisible()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(fakePageMock, setFullDate("JUN/14/2021")).Times(1);

    // Only year was changed
    pageMockWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2021/06/14 14:24:43", '/', ':')});
}

TEST_F(ClockPageHandlerTest, WeekdayChangeHandledCorrectly)
{
    setupMock();

    using ::testing::Return;

    EXPECT_CALL(fakePageMock, isVisible()).Times(1).WillOnce(Return(true));

    EXPECT_CALL(fakePageMock, setWeekday(std::string_view("TUE"))).Times(1);
    EXPECT_CALL(fakePageMock, setFullDate("JUN/23/2020")).Times(1);

    pageMockWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/23 14:24:43", '/', ':')});
}
TEST_F(ClockPageHandlerTest, WeekdayChangeFromSundayToMondayHandledCorrectly)
{
    setupMock();

    using ::testing::Return;

    EXPECT_CALL(fakePageMock, isVisible()).Times(2).WillRepeatedly(Return(true));

    EXPECT_CALL(fakePageMock, setWeekday(std::string_view("SUN"))).Times(1);
    EXPECT_CALL(fakePageMock, setFullDate("JUN/28/2020")).Times(1);

    pageMockWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/28 14:24:43", '/', ':')});

    EXPECT_CALL(fakePageMock, setWeekday(std::string_view("MON"))).Times(1);
    EXPECT_CALL(fakePageMock, setFullDate("JUN/29/2020")).Times(1);

    pageMockWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/29 14:24:43", '/', ':')});
}

TEST_F(ClockPageHandlerTest, FormattingDateWorkCorrectlyForDigitsWithoutLeadingZero)
{
    setDefaultDate();

    using ::testing::Return;

    fakeView.show();

    pageWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/22 15:24:43", '/', ':')});
    EXPECT_EQ(fakeView.getFullDate(), "JUN/22/2020");
}

TEST_F(ClockPageHandlerTest, FormattingDateWorkCorrectlyForDigitsWithLeadingZero)
{
    setDefaultDate();

    using ::testing::Return;

    fakeView.show();

    pageWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/2 15:24:43", '/', ':')});
    EXPECT_EQ(fakeView.getFullDate(), "JUN/02/2020");
}

TEST_F(ClockPageHandlerTest, FormattingDateWorkCorrectlyForDigitsWithTrailingZero)
{
    setDefaultDate();

    using ::testing::Return;

    fakeView.show();

    pageWatchHandler->handleEvent(
        {Graphics::Events::EventGroup::DateTime,
         Graphics::Events::TDateTimeEvents::DateTimeChanged,
         TimeWrapper("2020/06/20 15:24:43", '/', ':')});
    EXPECT_EQ(fakeView.getFullDate(), "JUN/20/2020");
}