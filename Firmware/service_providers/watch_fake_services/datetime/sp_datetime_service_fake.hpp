#pragma once

#include "ih/sp_idatetime_service.hpp"

namespace ServiceProviders::DateTimeService
{

class DateTimeServiceFake
    :   public IDateTimeService
{

public:

    explicit DateTimeServiceFake()noexcept;

    ~DateTimeServiceFake()override;

public:

    void launchService()noexcept override;

    void calibrateSource()noexcept override;

    void syncronizeWithBleDts()noexcept override;

private:
    class DatetimeSimulatorImpl;
    std::unique_ptr<DatetimeSimulatorImpl> m_pDatetimeSimImpl;
};

}