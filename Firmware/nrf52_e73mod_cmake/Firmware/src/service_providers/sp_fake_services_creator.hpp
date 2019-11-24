#pragma once

#include "ih/sp_iservice_creator.hpp"

namespace ServiceProviders::BatteryService
{
    class IBatteryLevelAppService;
}

namespace ServiceProviders
{

class FakeServiceCreator
    :   public IServiceCreator
{

public:

    [[nodiscard]] std::unique_ptr<BatteryService::IBatteryLevelAppService>
    getBatteryService() override;

    ~FakeServiceCreator()override = default;

};

std::unique_ptr<IServiceCreator> getFakeServiceCreator();

}