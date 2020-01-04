#include "sp_fake_services_creator.hpp"

#include "ih/sp_ibattery_service.hpp"
#include "ih/sp_iservice_creator.hpp"

#include "battery/sp_battery_service_fake.hpp"
#include "heartrate/sp_heartrate_service_fake.hpp"

namespace ServiceProviders
{

std::unique_ptr<BatteryService::IBatteryLevelAppService>
FakeServiceCreator::getBatteryService()
{
    return std::make_unique<BatteryService::BatteryServiceFake>(
        BatteryService::Settings::MeasurmentPeriod
    );
}

std::unique_ptr<HeartrateService::IHeartrateService>
FakeServiceCreator::getHeartrateService()
{
    return std::make_unique<HeartrateService::HeartrateServiceFake>();
}

std::unique_ptr<IServiceCreator> getFakeServiceCreator()
{
    return std::make_unique<FakeServiceCreator>();
}

};
