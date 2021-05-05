#include "sp_heartrate_service_fake.hpp"


namespace ServiceProviders::HeartrateService
{

class HeartrateServiceFake::HeartrateSimulatorImpl
{

public:

    void startMeasure()noexcept {}; //Just for test

};



HeartrateServiceFake::HeartrateServiceFake()noexcept
    :   m_pHeartrateSimImpl{ std::make_unique<HeartrateSimulatorImpl>() }
{
}

HeartrateServiceFake::~HeartrateServiceFake() = default;

void
HeartrateServiceFake::startMeasure()noexcept
{
    m_pHeartrateSimImpl->startMeasure();
}

}