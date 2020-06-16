#include "inc/ble/nordic_ble/ble_custom_service.hpp"

#include "logger/logger_service.hpp"
#include "utils/CallbackConnector.hpp"

#include "sdk_common.h"
#include "ble_srv_common.h"
#include "nrf_gpio.h"
#include "boards.h"
#include "nrf_log.h"
#include "nrf_sdh_ble.h"

#include <cstring>

namespace Ble::CustomService
{

CustomService::CustomService()
    :   m_serviceHandle{}
    ,   m_customValueHandles{}
    ,   m_connectionHandle{ BLE_CONN_HANDLE_INVALID }
    ,   m_uuidType{}
{
    initEventHandler();
    initCustomService();
}

void CustomService::initEventHandler()
{
        NRF_SDH_BLE_OBSERVER(
            m_serviceEvent
        ,   ServiceObserverPriority
        ,   serviceBleEventHandler
        ,   this
    );
    
 }

void CustomService::bleEventHandler( ble_evt_t const * _pEvent )
{
    if( _pEvent == nullptr )
        return;

    switch (_pEvent->header.evt_id)
    {
        case BLE_GAP_EVT_CONNECTED:
            //on_connect(p_cus, p_ble_evt);
            break;

        case BLE_GAP_EVT_DISCONNECTED:
            //on_disconnect(p_cus, p_ble_evt);
            break;

        case BLE_GATTS_EVT_WRITE:
            //on_write(p_cus, p_ble_evt);
            break;
/* Handling this event is not necessary
        case BLE_GATTS_EVT_EXCHANGE_MTU_REQUEST:
            NRF_LOG_INFO("EXCHANGE_MTU_REQUEST event received.\r\n");
            break;
*/
        default:
            // No implementation needed.
            break;
    }

}

void CustomService::serviceBleEventHandler( ble_evt_t const * _pEvent, void * _pContext )
{
    TThis* pThis = reinterpret_cast<TThis*>( _pContext );
    pThis->bleEventHandler( _pEvent );

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

};