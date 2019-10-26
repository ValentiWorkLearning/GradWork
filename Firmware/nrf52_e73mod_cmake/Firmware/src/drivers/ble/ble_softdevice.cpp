#include "ble_softdevice.hpp"

#include "ble_stack_constants.hpp"

#include "CallbackConnector.hpp"

#include "app_error.h"

#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_qwr.h"

namespace Ble::Stack
{


BleStackKeeper::BleStackKeeper()
    :   m_connectionHandle{ BLE_CONN_HANDLE_INVALID }
{
    bleStackInit();
    initGattModule();
}

void BleStackKeeper::initGattModule()
{
}

void BleStackKeeper::bleStackInit()
{
    ret_code_t errCode{};

    errCode = nrf_sdh_enable_request();

    std::uint32_t ramStart{};

    // Configure the BLE stack using the default settings.
    // Fetch the start address of the application RAM.
    errCode = nrf_sdh_ble_default_cfg_set(
            StackConstants::AppBleConnCfgTag
        ,   &ramStart
    );
    APP_ERROR_CHECK( errCode );

    // Enable BLE stack.
    errCode = nrf_sdh_ble_enable( &ramStart );
    APP_ERROR_CHECK( errCode );

    auto bleEventHandlerCallback = cbc::obtain_connector(
        [ this ]( ble_evt_t const * _pEvent, void * _pContext )
        {
            return bleEventHandler( _pEvent,_pContext );
        }
    );

    // Register a handler for BLE events.
    NRF_SDH_BLE_OBSERVER(
            m_bleObserver
        ,   StackConstants::ObserverPriority
        ,   bleEventHandlerCallback
        ,   nullptr
    );
}

void BleStackKeeper::bleEventHandler( ble_evt_t const* _pBleEvent, void * _pContext )
{
    //copied as is from https://github.com/NordicPlayground/nRF52-Bluetooth-Course/blob/master/main.c

        ret_code_t errCode { NRF_SUCCESS };

    switch (_pBleEvent->header.evt_id)
    {
        case BLE_GAP_EVT_DISCONNECTED:
            //NRF_LOG_INFO("Disconnected.");
            // LED indication will be changed when advertising starts.
            break;

        case BLE_GAP_EVT_CONNECTED:
            //NRF_LOG_INFO("Connected.");
            //errCode = bsp_indication_set( BSP_INDICATE_CONNECTED );
            APP_ERROR_CHECK( errCode );

            m_connectionHandle = _pBleEvent->evt.gap_evt.conn_handle;
            errCode = nrf_ble_qwr_conn_handle_assign( &m_qwr, m_connectionHandle );

            APP_ERROR_CHECK( errCode );
            break;

        case BLE_GAP_EVT_PHY_UPDATE_REQUEST:
        {
            //NRF_LOG_DEBUG("PHY update request.");

            ble_gap_phys_t const phys =
            {
                .tx_phys = BLE_GAP_PHY_AUTO,
                .rx_phys = BLE_GAP_PHY_AUTO,
            };
            errCode = sd_ble_gap_phy_update( _pBleEvent->evt.gap_evt.conn_handle, &phys );

            APP_ERROR_CHECK( errCode );
        } break;

        case BLE_GATTC_EVT_TIMEOUT:
            // Disconnect on GATT Client timeout event.
            //NRF_LOG_DEBUG("GATT Client Timeout.");

            errCode = sd_ble_gap_disconnect(
                    _pBleEvent->evt.gattc_evt.conn_handle
                ,   BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION
            );

            APP_ERROR_CHECK( errCode );
            break;

        case BLE_GATTS_EVT_TIMEOUT:
            // Disconnect on GATT Server timeout event.
            //NRF_LOG_DEBUG("GATT Server Timeout.");

            errCode = sd_ble_gap_disconnect(
                    _pBleEvent->evt.gatts_evt.conn_handle
                ,   BLE_HCI_REMOTE_USER_TERMINATED_CONNECTION
            );

            APP_ERROR_CHECK( errCode );
            break;

        default:
            // No implementation needed.
            break;
    }
}

nrf_ble_qwr_t BleStackKeeper::m_qwr{};

std::unique_ptr<BleStackKeeper> createBleStackKeeper()
{
    return std::make_unique<BleStackKeeper>();
}

};