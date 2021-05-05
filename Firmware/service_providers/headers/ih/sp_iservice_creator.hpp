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
    getBatteryService()noexcept = 0;

    [[nodiscard]] virtual std::unique_ptr<HeartrateService::IHeartrateService>
    getHeartrateService()noexcept = 0;

    [[nodiscard]] virtual std::unique_ptr<DateTimeService::IDateTimeService>
    getDateTimeService()noexcept = 0;

    virtual ~IServiceCreator() = default;
};

}