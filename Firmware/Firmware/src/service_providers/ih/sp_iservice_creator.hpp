#pragma once

#include <memory>

namespace ServiceProviders::BatteryService
{
    class IBatteryLevelAppService;
}

namespace ServiceProviders::HeartrateService
{
    class IHeartrateService;
}

namespace ServiceProviders::DateTimeService
{
    class IDateTimeService;
}

namespace ServiceProviders
{

class IServiceCreator
{

public:

    [[nodiscard]] virtual std::unique_ptr<BatteryService::IBatteryLevelAppService>
    getBatteryService() = 0;

    [[nodiscard]] virtual std::unique_ptr<HeartrateService::IHeartrateService>
    getHeartrateService() = 0;

    [[nodiscard]] virtual std::unique_ptr<DateTimeService::IDateTimeService>
    getDateTimeService() = 0;

    virtual ~IServiceCreator() = default;
};

}