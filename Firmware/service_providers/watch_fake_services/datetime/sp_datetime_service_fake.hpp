#pragma once

#include "ih/sp_idatetime_service.hpp"

namespace ServiceProviders::DateTimeService
{

class DateTimeServiceFake
    :   public IDateTimeService
{

public:

    explicit DateTimeServiceFake();

    ~DateTimeServiceFake()override;

public:

    void launchService() override;

    void calibrateSource() override;

    void syncronizeWithBleDts() override;

private:
    class DatetimeSimulatorImpl;
    std::unique_ptr<DatetimeSimulatorImpl> m_pDatetimeSimImpl;
};

}