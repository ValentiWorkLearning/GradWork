#pragma once
#include <gtest/gtest.h>

#include "widgets_layer/pages/clock_page/gs_clock_page_handler.hpp"

#include "clock_watch_fake_view.hpp"

#include <memory>

class ClockPageHandlerTest : public ::testing::Test
{

protected:
    void SetUp() override
    {
        setupTimeZoneEnvironment();

        pageWatchHandler = Graphics::Views::createPageWatchHandler(&fakeView);
        pageMockWatchHandler = Graphics::Views::createPageWatchHandler(&fakePageMock);
    }

    void setDefaultDate()
    {
        using ::testing::Return;

        fakeView.show();

        pageWatchHandler->handleEvent(
            {Graphics::Events::EventGroup::DateTime,
             Graphics::Events::TDateTimeEvents::DateTimeChanged,
             TimeWrapper("2020/06/22 14:24:43", '/', ':')});
    }

    void setupMock()
    {
        using ::testing::Return;

        EXPECT_CALL(fakePageMock, isVisible()).Times(1).WillOnce(Return(true));

        EXPECT_CALL(fakePageMock, setHours("14")).Times(1);
        EXPECT_CALL(fakePageMock, setMinutes("24")).Times(1);
        EXPECT_CALL(fakePageMock, setSeconds("43")).Times(1);
        EXPECT_CALL(fakePageMock, setWeekday(std::string_view("MON"))).Times(1);
        EXPECT_CALL(fakePageMock, setFullDate("JUN/22/2020")).Times(1);

        pageMockWatchHandler->handleEvent(
            {Graphics::Events::EventGroup::DateTime,
             Graphics::Events::TDateTimeEvents::DateTimeChanged,
             TimeWrapper("2020/06/22 14:24:43", '/', ':')});
    }

protected:
    FakeClockPageMock fakePageMock;
    FakeClockPage fakeView{Graphics::Views::IClockWatchPage::ClockPageName};
    std::unique_ptr<Graphics::IEventHandler> pageWatchHandler;
    std::unique_ptr<Graphics::IEventHandler> pageMockWatchHandler;

private:
    void setupTimeZoneEnvironment()
    {
        // https://github.com/ikonopistsev/btdef/blob/4893ca36f5a251147c57ecfa460acfbe717f69c3/util/time_zone.hpp
        // https://science.ksc.nasa.gov/software/winvn/userguide/3_1_4.htm
#ifdef WIN32
        _putenv_s("TZ", "UTC");
        _tzset();
#else
        putenv("TZ=UTC");
        tzset();
#endif
    }
};
