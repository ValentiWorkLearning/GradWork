#include "ble_softdevice.hpp"

#include "ble_stack_constants.hpp"

#include "CallbackConnector.hpp"

#include "app_error.h"

#include "nrf_sdh.h"
#include "nrf_sdh_ble.h"
#include "nrf_ble_qwr.h"

#include "logger_service.hpp"

namespace
{
    BLE_ADVERTISING_DEF( m_advertising );       /**< Advertising module instance. */
    NRF_BLE_QWR_DEF( m_qwr );                   /**< Context for the Queued Write module.*/
    NRF_BLE_GATT_DEF( m_gatt );                 /**< GATT module instance. */

    //TODO: this uuids must be placed as constexpr uuids for custome services. This just for compilation.
    static ble_uuid_t m_adv_uuids[] =                       /**< Universally unique service identifiers. */
    {
        {BLE_UUID_PLX_SERVICE, BLE_UUID_TYPE_BLE},
        {BLE_UUID_BATTERY_SERVICE, BLE_UUID_TYPE_BLE},
        {BLE_UUID_DEVICE_INFORMATION_SERVICE, BLE_UUID_TYPE_BLE}
    };
}

namespace Ble::Stack
{


BleStackKeeper::BleStackKeeper()
    :   m_connectionHandle{ BLE_CONN_HANDLE_INVALID }
{
    bleStackInit();
    initGapModule();
    initGatt();
    initAdvertising();

    initServices();

    initConnectionParams();
    initPeerManager();
}

void BleStackKeeper::initGapModule()
{
    ret_code_t              errCode{};
    ble_gap_conn_params_t   gapConnectionParams{};
    ble_gap_conn_sec_mode_t securityMode{};

    BLE_GAP_CONN_SEC_MODE_SET_OPEN( &securityMode );

    namespace GapParams = Ble::Stack::GapSettings;

    errCode = sd_ble_gap_device_name_set(
            &securityMode
        ,   reinterpret_cast<const std::uint8_t*>( GapParams::DeviceName.data() )
        ,   GapParams::DeviceName.length()
    );
    APP_ERROR_CHECK( errCode );

    errCode = sd_ble_gap_appearance_set( BLE_APPEARANCE_GENERIC_WATCH );
    APP_ERROR_CHECK( errCode );

    gapConnectionParams.min_conn_interval = GapParams::MinConnectionInterval;
    gapConnectionParams.max_conn_interval = GapParams::MaxConnectionInterval;
    gapConnectionParams.slave_latency     = GapParams::SlaveLatency;
    gapConnectionParams.conn_sup_timeout  = GapParams::ConnectionSupervisoryTimeout;

    errCode = sd_ble_gap_ppcp_set( &gapConnectionParams );

    APP_ERROR_CHECK( errCode );
}

void BleStackKeeper::initGatt()
{
    auto gattEventCallback = cbc::obtain_connector(
        [ this ]( nrf_ble_gatt_t * _pGatt, nrf_ble_gatt_evt_t const * _pEvent )
        {
            return gattEventHandler( _pGatt,_pEvent );
        }
    );

    ret_code_t errorCode = nrf_ble_gatt_init( &m_gatt, gattEventCallback );
    APP_ERROR_CHECK( errorCode );
}

void BleStackKeeper::gattEventHandler( nrf_ble_gatt_t * _pGatt, nrf_ble_gatt_evt_t const * _pEvent )
{
    if ( _pEvent->evt_id == NRF_BLE_GATT_EVT_ATT_MTU_UPDATED )
    {
        Logger::Instance().logDebug(
            "GATT ATT MTU on connection 0x%x changed to %d."
        );
        // NRF_LOG_INFO("GATT ATT MTU on connection 0x%x changed to %d.",
        //              p_evt->conn_handle,
        //              p_evt->params.att_mtu_effective);
    }
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
            Logger::Instance().logDebug("Disconnected.");
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
            Logger::Instance().logDebug( "PHY update request." );

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
            Logger::Instance().logDebug( "GATT Client Timeout." );

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



void BleStackKeeper::initAdvertising()
{
    ret_code_t errCode{};
    ble_advertising_init_t initAdvertisingParams{};

    initAdvertisingParams.advdata.name_type               = BLE_ADVDATA_FULL_NAME;
    initAdvertisingParams.advdata.include_appearance      = true;
    initAdvertisingParams.advdata.flags                   = BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE;
    initAdvertisingParams.advdata.uuids_complete.uuid_cnt = sizeof(m_adv_uuids) / sizeof(m_adv_uuids[0]);
    initAdvertisingParams.advdata.uuids_complete.p_uuids  = m_adv_uuids;

    namespace AdvertisingSettings = Ble::Stack::AdvertisingSettings;

    initAdvertisingParams.config.ble_adv_fast_enabled  = true;
    initAdvertisingParams.config.ble_adv_fast_interval = AdvertisingSettings::Interval.count();
    initAdvertisingParams.config.ble_adv_fast_timeout  = AdvertisingSettings::Duration.count();

    auto advertisingEventCallback = cbc::obtain_connector(
        [ this ]( ble_adv_evt_t _pAdvertisingEvent )
        {
            return advertisingEventHandler( _pAdvertisingEvent );
        }
    );

    initAdvertisingParams.evt_handler = advertisingEventCallback;

    errCode = ble_advertising_init( &m_advertising, &initAdvertisingParams );
    APP_ERROR_CHECK( errCode );

    ble_advertising_conn_cfg_tag_set( &m_advertising, StackConstants::AppBleConnCfgTag );
}

void BleStackKeeper::advertisingEventHandler( ble_adv_evt_t _pAdvertisingEvent )
{
    ret_code_t errorCode{};

    switch ( _pAdvertisingEvent )
    {
        case BLE_ADV_EVT_FAST:
            Logger::Instance().logDebug( "Fast advertising." );
            // errorCode = bsp_indication_set(BSP_INDICATE_ADVERTISING);
            APP_ERROR_CHECK(errorCode);
            break;

        case BLE_ADV_EVT_IDLE:
            //sleep_mode_enter();
            break;

        default:
            break;
    }
}

void BleStackKeeper::initPeerManager()
{
    ble_gap_sec_params_t securityParams{};
    ret_code_t           errorCode{};

    errorCode = pm_init();
    APP_ERROR_CHECK( errorCode );

    namespace Security = Ble::Stack::SecurityParams;

    // Security parameters to be used for all security procedures.
    securityParams.bond           = Security::Bonding;
    securityParams.mitm           = Security::ManInTheMiddle;
    securityParams.lesc           = Security::LeSecureConnections;
    securityParams.keypress       = Security::KeypressNotifications;
    securityParams.io_caps        = Security::IoCapabilities;
    securityParams.oob            = Security::OutOfBand;
    securityParams.min_key_size   = Security::MinKeySize;
    securityParams.max_key_size   = Security::MaxKeySize;
    securityParams.kdist_own.enc  = 1;
    securityParams.kdist_own.id   = 1;
    securityParams.kdist_peer.enc = 1;
    securityParams.kdist_peer.id  = 1;

    errorCode = pm_sec_params_set( &securityParams );
    APP_ERROR_CHECK( errorCode );


    auto peerEventCallback = cbc::obtain_connector(
        [ this ]( pm_evt_t const * _pPeerEvent )
        {
            return peerManagerEventHandler( _pPeerEvent );
        }
    );

    errorCode = pm_register( peerEventCallback );
    APP_ERROR_CHECK( errorCode );
}

void BleStackKeeper::connectionParamsEventHandler( ble_conn_params_evt_t * _pEvent )
{
    ret_code_t errCode{};

    if ( _pEvent->evt_type == BLE_CONN_PARAMS_EVT_FAILED )
    {
        errCode = sd_ble_gap_disconnect( m_connectionHandle, BLE_HCI_CONN_INTERVAL_UNACCEPTABLE );
        APP_ERROR_CHECK( errCode );
    }
}

void BleStackKeeper::connectionParamsErrorHandler( std::uint32_t _nrfError )
{

}


void BleStackKeeper::initConnectionParams()
{
    ret_code_t             errCode{};
    ble_conn_params_init_t connectionParams{};

    namespace ConnectionSettings = Ble::Stack::ConnectionParams;


    auto connectionParamsEventCallback = cbc::obtain_connector(
        [ this ]( ble_conn_params_evt_t* _pEvent )
        {
            return connectionParamsEventHandler( _pEvent );
        }
    );

    auto connectionParamsErrorCallback = cbc::obtain_connector(
        [ this ]( std::uint32_t _nrfError )
        {
            return connectionParamsErrorHandler( _nrfError );
        }
    );

    connectionParams.p_conn_params                  = nullptr;
    connectionParams.first_conn_params_update_delay = ConnectionSettings::FirstConnectionParamsUpdateDelay;
    connectionParams.next_conn_params_update_delay  = ConnectionSettings::NextConnectionParamsUpdateDelay;
    connectionParams.max_conn_params_update_count   = ConnectionSettings::MaxConnectionParamsUpdateCount;
    connectionParams.start_on_notify_cccd_handle    = BLE_GATT_HANDLE_INVALID;
    connectionParams.disconnect_on_fail             = false;
    connectionParams.evt_handler                    = connectionParamsEventCallback;
    connectionParams.error_handler                  = connectionParamsErrorCallback;

    errCode = ble_conn_params_init( &connectionParams );
    APP_ERROR_CHECK( errCode );
}

void BleStackKeeper::peerManagerEventHandler( pm_evt_t const * _pPeerEvent )
{
    ret_code_t errCode{};

    switch ( _pPeerEvent->evt_id )
    {
        case PM_EVT_BONDED_PEER_CONNECTED:
        {
            Logger::Instance().logDebug(  "Connected to a previously bonded device." );
        } break;

        case PM_EVT_CONN_SEC_SUCCEEDED:
        {
            Logger::Instance().logDebug(  "Connection secured: role: %d, conn_handle: 0x%x, procedure: %d." );
            //              ble_conn_state_role( _pPeerEvent->conn_handle ),
            //              _pPeerEvent->conn_handle,
            //              _pPeerEvent->params.conn_sec_succeeded.procedure );
        } break;

        case PM_EVT_CONN_SEC_FAILED:
        {
            /* Often, when securing fails, it shouldn't be restarted, for security reasons.
             * Other times, it can be restarted directly.
             * Sometimes it can be restarted, but only after changing some Security Parameters.
             * Sometimes, it cannot be restarted until the link is disconnected and reconnected.
             * Sometimes it is impossible, to secure the link, or the peer device does not support it.
             * How to handle this error is highly application dependent. */
        } break;

        case PM_EVT_CONN_SEC_CONFIG_REQ:
        {
            // Reject pairing request from an already bonded peer.
            pm_conn_sec_config_t conn_sec_config = {.allow_repairing = false};
            pm_conn_sec_config_reply(_pPeerEvent->conn_handle, &conn_sec_config);
        } break;

        case PM_EVT_STORAGE_FULL:
        {
            // Run garbage collection on the flash.
            errCode = fds_gc();
            if (errCode == FDS_ERR_NO_SPACE_IN_QUEUES)
            {
                // Retry.
            }
            else
            {
                APP_ERROR_CHECK( errCode );
            }
        } break;

        case PM_EVT_PEERS_DELETE_SUCCEEDED:
        {
            startAdvertising( EraseBondsConfig::DontEraseBounds );
        } break;

        case PM_EVT_PEER_DATA_UPDATE_FAILED:
        {
            // Assert.
            APP_ERROR_CHECK( _pPeerEvent->params.peer_data_update_failed.error );
        } break;

        case PM_EVT_PEER_DELETE_FAILED:
        {
            // Assert.
            APP_ERROR_CHECK( _pPeerEvent->params.peer_delete_failed.error );
        } break;

        case PM_EVT_PEERS_DELETE_FAILED:
        {
            // Assert.
            APP_ERROR_CHECK( _pPeerEvent->params.peers_delete_failed_evt.error );
        } break;

        case PM_EVT_ERROR_UNEXPECTED:
        {
            // Assert.
            APP_ERROR_CHECK( _pPeerEvent->params.error_unexpected.error );
        } break;

        case PM_EVT_CONN_SEC_START:
        case PM_EVT_PEER_DATA_UPDATE_SUCCEEDED:
        case PM_EVT_PEER_DELETE_SUCCEEDED:
        case PM_EVT_LOCAL_DB_CACHE_APPLIED:
        case PM_EVT_LOCAL_DB_CACHE_APPLY_FAILED:
            // This can happen when the local DB has changed.
        case PM_EVT_SERVICE_CHANGED_IND_SENT:
        case PM_EVT_SERVICE_CHANGED_IND_CONFIRMED:
        default:
            break;
    }
}


void BleStackKeeper::startAdvertising( EraseBondsConfig _eraseBonds )
{
    if( _eraseBonds == EraseBondsConfig::EraseBoundsPolicy )
    {
        deleteBonds();
        // Advertising is started by PM_EVT_PEERS_DELETED_SUCEEDED event
    }
    else
    {
        ret_code_t errCode = ble_advertising_start( &m_advertising, BLE_ADV_MODE_FAST );
        APP_ERROR_CHECK( errCode );
    }
}

void BleStackKeeper::deleteBonds()
{
    ret_code_t errCode{};

    Logger::Instance().logDebug( "Erase bonds!" );

    errCode = pm_peers_delete();
    APP_ERROR_CHECK( errCode );
}


void BleStackKeeper::initServices()
{
    //Here we init services.
}

std::unique_ptr<BleStackKeeper> createBleStackKeeper()
{
    return std::make_unique<BleStackKeeper>();
}

};