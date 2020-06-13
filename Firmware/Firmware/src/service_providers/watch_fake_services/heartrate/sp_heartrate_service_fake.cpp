#include "sp_heartrate_service_fake.hpp"


namespace ServiceProviders::HeartrateService
{

class HeartrateServiceFake::HeartrateSimulatorImpl
{

public:

    void startMeasure(){}; //Just for test

};



HeartrateServiceFake::HeartrateServiceFake()
    :   m_pHeartrateSimImpl{ std::make_unique<HeartrateSimulatorImpl>() }
{
}

HeartrateServiceFake::~HeartrateServiceFake() = default;

void
HeartrateServiceFake::startMeasure()
{
    m_pHeartrateSimImpl->startMeasure();
}

}