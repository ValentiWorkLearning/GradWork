#include "inc/ble/ble_battery_service.hpp"

#include "ble.h"
#include "ble_srv_common.h"
#include "ble_bas.h"

#include "app_error.h"

namespace Ble::BatteryService
{

static constexpr std::uint16_t ServiceUuid = BLE_UUID_BATTERY_SERVICE;
static constexpr std::uint8_t ServiceType = BLE_UUID_TYPE_BLE;

BLE_BAS_DEF(m_bas);

BatteryLevelService::BatteryLevelService()
{
    initService();
}

void BatteryLevelService::initService()
{
    ret_code_t errorCode{};
    ble_bas_init_t batteryServiceInit{};

    batteryServiceInit.bl_rd_sec        = SEC_OPEN;
    batteryServiceInit.bl_cccd_wr_sec   = SEC_OPEN;
    batteryServiceInit.bl_report_rd_sec = SEC_OPEN;

    batteryServiceInit.evt_handler          = nullptr;
    batteryServiceInit.support_notification = true;
    batteryServiceInit.p_report_ref         = nullptr;
    batteryServiceInit.initial_batt_level   = InitialBatteryLevel;

    errorCode = ble_bas_init( &m_bas, &batteryServiceInit );
    APP_ERROR_CHECK( errorCode );
}

void BatteryLevelService::onBatteryLevelChanged ( std::uint8_t _newBatteryLevel )
{
    ret_code_t errorCode{};
    std::uint8_t levelToSet{ _newBatteryLevel };

    errorCode = ble_bas_battery_level_update(
            &m_bas
        ,   levelToSet
        ,   BLE_CONN_HANDLE_ALL
    );

    if (
                ( errorCode != NRF_SUCCESS )
            &&  ( errorCode != NRF_ERROR_INVALID_STATE )
            &&  ( errorCode != NRF_ERROR_RESOURCES )
            &&  ( errorCode != NRF_ERROR_BUSY )
            &&  ( errorCode != BLE_ERROR_GATTS_SYS_ATTR_MISSING )
       )
    {
        APP_ERROR_CHECK( errorCode );
    }
}

}