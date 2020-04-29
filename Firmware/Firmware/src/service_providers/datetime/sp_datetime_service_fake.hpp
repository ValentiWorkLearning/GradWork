#pragma once

#include "ih/sp_idatetime_service.hpp"

#include "FastPimpl.hpp"
#include "Platform.hpp"

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

    static constexpr inline  std::size_t kImplSize =  Platform::DateTimeImplSize;
    static constexpr inline  std::size_t kImplAlignment = Platform::DateTimeAlignment;

private:

    class DatetimeSimulatorImpl;
    Utils::FastPimpl<DatetimeSimulatorImpl,kImplSize,kImplAlignment> m_pDatetimeSimImpl;
};

}