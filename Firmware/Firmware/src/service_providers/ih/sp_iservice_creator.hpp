#pragma once

#include <memory>

namespace ServiceProviders::BatteryService
{
    class IBatteryLevelAppService;
}

namespace ServiceProviders
{

class IServiceCreator
{

public:

    [[nodiscard]] virtual std::unique_ptr<BatteryService::IBatteryLevelAppService>
    getBatteryService() = 0;

    virtual ~IServiceCreator() = default;
};

}