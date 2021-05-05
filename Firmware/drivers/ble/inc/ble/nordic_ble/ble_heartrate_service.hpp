#pragma once

#include "ih/drivers/ih_ble_heartrate_service.hpp"

namespace Ble::HeartrateService
{

class NordicHeartrateService
    :   public IHeartrateService
{

public:

    NordicHeartrateService()noexcept;
    ~NordicHeartrateService()override;

public:
    void onHeartrateChanged ( std::uint8_t _newHeartrateLevel )noexcept override;

    void setSensorLocation( SensorLocation _sensorLocation )noexcept override;

private:
    void initService()noexcept;
};

}
