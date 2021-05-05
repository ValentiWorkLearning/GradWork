#pragma once

#include "ih/sp_iheartrate_service.hpp"

#include <memory>

namespace ServiceProviders::HeartrateService
{

class HeartrateServiceFake :
    public IHeartrateService
{

public:

    explicit HeartrateServiceFake()noexcept;

    ~HeartrateServiceFake();

public:

    void startMeasure()noexcept override;

private:

    class HeartrateSimulatorImpl;
    std::unique_ptr<HeartrateSimulatorImpl> m_pHeartrateSimImpl;
};

}
