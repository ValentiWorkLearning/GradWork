#include "ble_datetime_service.hpp"

#include "logger/logger_service.hpp"
#include "utils/CallbackConnector.hpp"

#include "app_error.h"
#include "ble_cts_c.h"
#include "ble_db_discovery.h"

namespace
{
    BLE_CTS_C_DEF( m_currentTimeService );

    void currentTimeServiceErrorHandler( uint32_t _nrfError )
    {
        APP_ERROR_HANDLER( _nrfError );
    }

}

namespace Ble::DateTimeService
{

DateTimeServiceNordic::DateTimeServiceNordic( const std::any& _pGattQueue )
{
    initService( _pGattQueue );
}

void
DateTimeServiceNordic::initService( const std::any& _pGattQueue )
{
    ret_code_t errorCode{};
    ble_cts_c_init_t ctsInit{};

    nrf_ble_gq_t* pGattQueue = std::any_cast<nrf_ble_gq_t*>( _pGattQueue );

    auto currentTimeServiceEventHandler = cbc::obtain_connector(
        [this](ble_cts_c_t* _currentTimeService, ble_cts_c_evt_t* _pEvent )
        {
            serviceEventHandler( _currentTimeService, _pEvent );
        }
    );

    ctsInit.evt_handler = currentTimeServiceEventHandler;
    ctsInit.error_handler = currentTimeServiceErrorHandler;
    ctsInit.p_gatt_queue = pGattQueue;
    errorCode = ble_cts_c_init( &m_currentTimeService, &ctsInit );
    APP_ERROR_CHECK( errorCode );

}

void
DateTimeServiceNordic::serviceEventHandler( ble_cts_c_t * _pCurrentTimeService, ble_cts_c_evt_t * _pEvent )
{
    ret_code_t errorCode{};

    switch ( _pEvent->evt_type )
    {
        case BLE_CTS_C_EVT_DISCOVERY_COMPLETE:
            Logger::Instance().logDebugEndl( "Current Time Service discovered on server." );
            errorCode = ble_cts_c_handles_assign(
                    &m_currentTimeService
                ,   _pEvent->conn_handle
                ,   &_pEvent->params.char_handles
            );
            APP_ERROR_CHECK( errorCode );
            break;

        case BLE_CTS_C_EVT_DISCOVERY_FAILED:
            Logger::Instance().logDebugEndl( "Current Time Service not found on server. " );
            // CTS not found in this case we just disconnect. There is no reason to stay
            // in the connection for this simple app since it all wants is to interact with CT
            // if (_pEvent->conn_handle != BLE_CONN_HANDLE_INVALID)
            // {
            //     errorCode = sd_ble_gap_disconnect(_pEvent->conn_handle,
            //                                      BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION);
            //     APP_ERROR_CHECK(errorCode);
            // }
            break;

        case BLE_CTS_C_EVT_DISCONN_COMPLETE:
            Logger::Instance().logDebugEndl( "Disconnect Complete." );
            break;

        case BLE_CTS_C_EVT_CURRENT_TIME:
            Logger::Instance().logDebugEndl( "Current Time received." );
            //current_time_print(_pEvent);
            break;

        case BLE_CTS_C_EVT_INVALID_TIME:
            Logger::Instance().logDebugEndl( "Invalid Time received." );
            break;

        default:
            break;
    }
}


void
DateTimeServiceNordic::handleDiscoveryEvent( const std::any& _pBleDbDiscoveryEvent )
{
    ble_db_discovery_evt_t* pEvent = std::any_cast<ble_db_discovery_evt_t*>( _pBleDbDiscoveryEvent );
    ble_cts_c_on_db_disc_evt( &m_currentTimeService, pEvent );
}

}