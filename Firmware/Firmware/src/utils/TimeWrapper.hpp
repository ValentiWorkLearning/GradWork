#pragma once

#include <ctime>
#include <string>
#include <array>
#include <chrono>

constexpr std::array Months = {
        "January"
    ,   "Febuary"
    ,   "March"
    ,   "April"
    ,   "May"
    ,   "June"
    ,   "July"
    ,   "August"
    ,   "September"
    ,   "November"
    ,   "December"
    ,   "Undefined"
};

constexpr std::array WeekDays = {
        "Sunday"
    ,   "Monday"
    ,   "Tuesday"
    ,   "Wednesday"
    ,   "Thursday"
    ,   "Friday"
    ,   "Saturday"
    ,   "Invalid"
};

class TimeWrapper
{

public:

    TimeWrapper();

    explicit TimeWrapper(const std::tm& _tm);

    std::string_view getMonthString() const;

    std::string_view getWeekDayString() const;

    std::chrono::seconds getSeconds()const;

    std::chrono::minutes getMinutes() const;

    std::chrono::hours getHours() const;

    std::uint8_t getDay() const;

    std::uint8_t getMonth()const;

    std::uint16_t getYear()const;

public:

    void addSecond();

    void addMinute();

private:

    std::tm m_internalTm;
};

inline TimeWrapper::TimeWrapper()
{
    std::time_t currentTime = std::time( nullptr );
    m_internalTm = *std::localtime( &currentTime );
}

inline TimeWrapper::TimeWrapper( const std::tm& _tm )
    :   m_internalTm{ _tm }
{
}


inline std::string_view
TimeWrapper::getMonthString() const
{
    std::uint8_t arrayIndex = m_internalTm.tm_mon;
    if (arrayIndex >= Months.size())
        return Months.back();

    return Months[arrayIndex];
}

inline std::string_view
TimeWrapper::getWeekDayString() const
{
    std::uint8_t arrayIndex = m_internalTm.tm_wday;
    if (arrayIndex > WeekDays.size())
        return WeekDays.back();

   return WeekDays[arrayIndex];
}

inline std::chrono::seconds TimeWrapper::getSeconds() const
{
    return std::chrono::seconds();
}


inline std::chrono::minutes TimeWrapper::getMinutes() const
{
    return std::chrono::minutes();
}

inline std::chrono::hours TimeWrapper::getHours() const
{
    return std::chrono::hours();
}

inline std::uint8_t TimeWrapper::getMonth() const
{
    return m_internalTm.tm_mon;
}

inline std::uint8_t TimeWrapper::getDay() const
{
    return m_internalTm.tm_mon;
}

inline std::uint16_t
TimeWrapper::getYear()const
{
    return m_internalTm.tm_year + 1900;
}

inline void
TimeWrapper::addSecond()
{
    std::tm currentTm = m_internalTm;
    currentTm.tm_sec = currentTm.tm_sec + 1;
    std::time_t curretTimeT = std::mktime( &currentTm );
    m_internalTm = *std::localtime( &curretTimeT );
}

inline void
TimeWrapper::addMinute()
{
    std::tm currentTm = m_internalTm;
    currentTm.tm_min = currentTm.tm_min + 1;
    std::time_t curretTimeT = std::mktime( &currentTm );
    m_internalTm = *std::localtime( &curretTimeT );
}