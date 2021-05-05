#pragma once

#include "ih/sp_iservice_creator.hpp"

namespace ServiceProviders
{

class FakeServiceCreator
    :   public IServiceCreator
{

public:

    [[nodiscard]] std::unique_ptr<BatteryService::IBatteryLevelAppService>
    getBatteryService()noexcept override;

    [[nodiscard]] std::unique_ptr<HeartrateService::IHeartrateService>
    getHeartrateService()noexcept override;

    [[nodiscard]] std::unique_ptr<DateTimeService::IDateTimeService>
    getDateTimeService()noexcept override;

    ~FakeServiceCreator()override = default;

};

std::unique_ptr<IServiceCreator> getFakeServiceCreator()noexcept;

}