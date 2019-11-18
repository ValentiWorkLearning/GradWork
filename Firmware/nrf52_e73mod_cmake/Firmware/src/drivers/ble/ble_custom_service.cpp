#include "ble_custom_service.hpp"

#include "sdk_common.h"
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"

#include <cstring>

namespace Ble::CustomService
{

CustomService::CustomService()
    :   m_serviceHandle{}
    ,   m_customValueHandles{}
    ,   m_connectionHandle{ BLE_CONN_HANDLE_INVALID }
    ,   m_uuidType{}
{
    initCustomService();
    initAdvertisment();
    initCustomCharacteric();
}

void CustomService::initCustomService()
{
    struct CustomServiceInit
    {
        std::uint8_t m_initialCustomValue;
        ble_srv_cccd_security_mode_t m_customValueCharAttribute;
    };

    ret_code_t errCode{};

    // Add Custom Service UUID
    ble_uuid128_t baseUuid{};
    std::memcpy(
            &baseUuid
        ,   CustomServiceUuid.data()
        ,   CustomServiceUuid.size()
    );

    errCode = sd_ble_uuid_vs_add( &baseUuid, &m_uuidType ); // Add the Custom Service

    APP_ERROR_CHECK( errCode );

    ble_uuid_t bleUuid{ ServiceUuid, m_uuidType };

    errCode = sd_ble_gatts_service_add(
            BLE_GATTS_SRVC_TYPE_PRIMARY
        ,   &bleUuid
        ,   &m_serviceHandle
    );

    APP_ERROR_CHECK( errCode );

}

void CustomService::initCustomCharacteric()
{

}

void CustomService::initAdvertisment()
{

}

};