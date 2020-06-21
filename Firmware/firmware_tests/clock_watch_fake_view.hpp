#pragma once

#include <gmock/gmock.h>

#include "ih/pages/gs_iclock_page_view.hpp"

#include "ih/gs_iwidget_object.hpp"
#include "ih/gs_itheme_controller.hpp"

#include <string>

template <typename PageBaseFake >
class FakeBasePage
	:	public PageBaseFake
{

public:

	MOCK_METHOD1(addWidget, void(Graphics::Widgets::IWidgetObject* _pWidget));
	MOCK_METHOD0(show, void());
	MOCK_METHOD0(hide, void());

	MOCK_CONST_METHOD0(isVisible, bool());
	MOCK_METHOD0(reloadStyle, void());

public:

	MOCK_CONST_METHOD0(getPageName, std::string_view());
	MOCK_CONST_METHOD0(getThemeController, const Graphics::Theme::IThemeController* ());

};

class FakeClockPage
	:	public FakeBasePage<Graphics::Views::IClockWatchPage>
{

public:

	MOCK_METHOD1(setHours, void(const std::string& _newHoursValue));
	MOCK_METHOD1(setMinutes, void(const std::string& _newMinutesValue));
	MOCK_METHOD1(setSeconds, void(const std::string& _newSecondsValue));
	MOCK_METHOD1(setWeekday, void(std::string_view _newWeekDay));
	MOCK_METHOD1(setFullDate, void(const std::string& _fullDate));
};