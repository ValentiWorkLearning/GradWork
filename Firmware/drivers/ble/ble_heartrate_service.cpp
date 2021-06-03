#include "inc/ble/nordic_ble/ble_heartrate_service.hpp"

#include "app_error.h"
#include "ble_hrs.h"

#include <cstdint>

namespace
{
BLE_HRS_DEF(m_hrs);
}

namespace Ble::HeartrateService
{

NordicHeartrateService::NordicHeartrateService() noexcept
{
    initService();
}

NordicHeartrateService::~NordicHeartrateService() = default;

void NordicHeartrateService::onHeartrateChanged(std::uint8_t _newHeartrateLevel) noexcept
{
    ret_code_t errorCode = ble_hrs_heart_rate_measurement_send(&m_hrs, _newHeartrateLevel);
    APP_ERROR_CHECK(errorCode);
}

void NordicHeartrateService::initService() noexcept
{
    ble_hrs_init_t heartrateDescriptor{};
    std::uint8_t bodySensorLocation = BLE_HRS_BODY_SENSOR_LOCATION_FINGER;

    heartrateDescriptor.evt_handler = nullptr;
    heartrateDescriptor.is_sensor_contact_supported = true;
    heartrateDescriptor.p_body_sensor_location = &bodySensorLocation;

    heartrateDescriptor.hrm_cccd_wr_sec = SEC_OPEN;
    heartrateDescriptor.bsl_rd_sec = SEC_OPEN;

    ret_code_t errorCode = ble_hrs_init(&m_hrs, &heartrateDescriptor);
    APP_ERROR_CHECK(errorCode);
}

void NordicHeartrateService::setSensorLocation(
    Ble::HeartrateService::SensorLocation _sensorLocation) noexcept
{
    // TODO me?
}

} // namespace Ble::HeartrateService
