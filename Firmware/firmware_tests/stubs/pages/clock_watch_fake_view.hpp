#pragma once

#include <gmock/gmock.h>

#include"base_mocked_page.hpp"

#include "ih/pages/gs_iclock_page_view.hpp"

class FakeClockPage
	:	public FakeBasePage<Graphics::Views::IClockWatchPage>
{

public:

	FakeClockPage( std::string_view _pageName )noexcept
		:	FakeBasePage{ _pageName  }
		,	m_hoursValue{ "00" }
		,	m_minutesValue{ "00" }
		,	m_secondsValue{ ":00" }
		,	m_weekdayValue{ "........." }
		,	m_fulldateValue{ "../../...." }
	{
	}

public:

	void setHours(const std::string& _newHoursValue)noexcept override
	{
		m_hoursValue = _newHoursValue;
	};

	void setMinutes(const std::string& _newMinutesValue)noexcept override
	{
		m_minutesValue = _newMinutesValue;
	};

	void setSeconds(const std::string& _newSecondsValue)noexcept override
	{
		m_secondsValue = _newSecondsValue;
	};

	void setWeekday(std::string_view _newWeekDay)noexcept override
	{
		m_weekdayValue = _newWeekDay;
	};

	void setFullDate(const std::string& _fullDate)noexcept override
	{
		m_fulldateValue = _fullDate;
	};

public:

	std::string_view getHours()const noexcept
	{
		return m_hoursValue;
	}

	std::string_view getMinutes()const noexcept
	{
		return m_minutesValue;
	}

	std::string_view getSeconds()const noexcept
	{
		return m_secondsValue;
	}

	std::string_view getWeekday()const noexcept
	{
		return m_weekdayValue;
	}

	std::string_view getFullDate()const noexcept
	{
		return m_fulldateValue;
	}

private:
	std::string m_hoursValue;
	std::string m_minutesValue;
	std::string m_secondsValue;
	std::string m_weekdayValue;
	std::string m_fulldateValue;
};


class FakeClockPageMock
	:	public FakeBasePageMock<Graphics::Views::IClockWatchPage>
{

public:
	MOCK_METHOD(void, setHours, (const std::string&), (noexcept,override));
	MOCK_METHOD(void, setMinutes, (const std::string&), (noexcept,override));
	MOCK_METHOD(void, setSeconds, (const std::string&), (noexcept,override));
	MOCK_METHOD(void, setWeekday, (std::string_view), (noexcept,override));
	MOCK_METHOD(void, setFullDate, (const std::string&), (noexcept,override));
};