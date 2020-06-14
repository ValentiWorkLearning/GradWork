#pragma once

#include "ih/sp_iheartrate_service.hpp"

#include <memory>

namespace ServiceProviders::HeartrateService
{

class HeartrateServiceFake :
    public IHeartrateService
{

public:

    explicit HeartrateServiceFake();

    ~HeartrateServiceFake();

public:

    void startMeasure() override;

private:

    class HeartrateSimulatorImpl;
    std::unique_ptr<HeartrateSimulatorImpl> m_pHeartrateSimImpl;
};

}
