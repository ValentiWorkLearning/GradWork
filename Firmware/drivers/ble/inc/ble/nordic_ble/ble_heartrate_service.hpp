#pragma once

#include "ih/drivers/ih_ble_heartrate_service.hpp"

namespace Ble::HeartrateService
{

class NordicHeartrateService
    :   public IHeartrateService
{

public:

    NordicHeartrateService();
    ~NordicHeartrateService()override = default;

public:
    void onHeartrateChanged ( std::uint8_t _newHeartrateLevel ) override;

    void setSensorLocation( SensorLocation _sensorLocation ) override;

private:
    void initService();
};

}
