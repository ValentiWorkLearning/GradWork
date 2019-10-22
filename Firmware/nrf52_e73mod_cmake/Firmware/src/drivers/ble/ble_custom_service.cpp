#include "ble_custom_service.hpp"

#include "sdk_common.h"
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"

#include <string>


namespace Ble::CustomService
{

CustomService::CustomService()
    :   m_serviceHandle{}
    ,   m_customValueHandles{}
    ,   m_connectionHandle{ BLE_CONN_HANDLE_INVALID }
    ,   m_uuidType{}
{
}

void CustomService::initCustomService()
{
    struct CustomServiceInit
    {
        std::uint8_t m_initialCustomValue;
        ble_srv_cccd_security_mode_t m_customValueCharAttribute;
    };

    // Add Custom Service UUID
    ble_uuid128_t baseUuid{};
    std::memcpy( baseUuid, UuidBase_BE.data(), UuidSize );

    errCode = sd_ble_uuid_vs_add( &baseUuid, &m_uuidType ); // Add the Custom Service

    if( errCode != NRF_SUCCESS )
    {
        throw std::exception( "Error while initializing custom service" );
    }

    ble_uuid_t bleUuid{ m_uuidType, ServiceUuid };

    errCode = sd_ble_gatts_service_add(
            BLE_GATTS_SRVC_TYPE_PRIMARY
        ,   bleUuid
        ,   m_serviceHandle
    );

    if( errCode != NRF_SUCCESS )
    {
        throw std::exception( "Error while initializing custom service" );
    }

}

void CustomService::initCustomCharacteric()
{

}

void CustomService::initAdvertisment()
{
    ret_code_t errCode{};
    nrf_ble_qwr_init_t qwrInit{};
    
    qwrInit.error_handler = nrf_qwr_error_handler;
    errCode = nrf_ble_qwr_init(  , &qwrInit );
}

};