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

namespace ServiceProviders
{

class IServiceCreator
{

public:

    [[nodiscard]] virtual std::unique_ptr<BatteryService::IBatteryLevelAppService>
    getBatteryService() = 0;

    [[nodiscard]] virtual std::unique_ptr<HeartrateService::IHeartrateService>
    getHeartrateService() = 0;

    virtual ~IServiceCreator() = default;
};

}