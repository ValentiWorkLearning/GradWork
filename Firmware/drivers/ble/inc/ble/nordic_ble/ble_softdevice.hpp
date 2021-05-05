#pragma once

#include "ih/drivers/ih_ible_softdevice.hpp"

#include "ih/drivers/ih_ble_service_factory.hpp"

#include "utils/SimpleSignal.hpp"
#include "utils/Noncopyable.hpp"

#include <memory>

#include <ble.h>

#include "nrf_ble_qwr.h"

#include "nordic_common.h"
#include "nrf.h"
#include "app_error.h"
#include "ble.h"
#include "ble_hci.h"
#include "ble_srv_common.h"
#include "ble_advdata.h"
#include "ble_advertising.h"
#include "ble_conn_params.h"
#include "nrf_sdh.h"
#include "nrf_sdh_soc.h"
#include "nrf_sdh_ble.h"
#include "app_timer.h"
#include "fds.h"
#include "peer_manager.h"
#include "bsp_btn_ble.h"

#include "ble_conn_state.h"
#include "nrf_ble_gatt.h"
#include "nrf_ble_qwr.h"
#include "nrf_pwr_mgmt.h"

#include "ble_stack_constants.hpp"

namespace Ble::CustomService
{
    class CustomService;
}

namespace Ble::Stack
{


class BleStackKeeper
    :   public IBleSoftDevice
{

public:

    BleStackKeeper( ServiceFactory::TBleFactoryPtr&& _pServiceCreator )noexcept;
    ~BleStackKeeper()override = default;

public:

    Ble::BatteryService::IBatteryLevelService& getBatteryService()noexcept override;

    const Ble::BatteryService::IBatteryLevelService& getBatteryService() const noexcept override;

    Ble::DateTimeService::IDateTimeService& getDateTimeService()noexcept override;

    const Ble::DateTimeService::IDateTimeService& getDateTimeService() const noexcept override;

private:

    void bleStackInit()noexcept;

    void bleEventHandler( ble_evt_t const* _pBleEvent )noexcept;

    static void bleEventHandlerLink( ble_evt_t const * _pBleEvent, void * _pContext )noexcept;

private:

    void initGapModule()noexcept;

    void initGatt()noexcept;

    void initDbDiscovery()noexcept;

    void gattEventHandler( nrf_ble_gatt_t* p_gatt, nrf_ble_gatt_evt_t const* p_evt )noexcept;

private:

    void initPeerManager()noexcept;

    void peerManagerEventHandler( pm_evt_t const* _pPeerEvent )noexcept;

    void peerListGet(pm_peer_id_t* _pPeers, uint32_t* pPeersSize)noexcept;

private:

    void initAdvertising()noexcept;

    void advertisingEventHandler( ble_adv_evt_t _pAdvertisingEvent )noexcept;

private:

    void initConnectionParams()noexcept;

    void connectionParamsEventHandler( ble_conn_params_evt_t* _pEvent )noexcept;

    void connectionParamsErrorHandler( std::uint32_t _nrfError )noexcept;

private:

    void initServices()noexcept;
    
private:

    using TThis = BleStackKeeper;

    enum class EraseBondsConfig
    {
            EraseBoundsPolicy
        ,   DontEraseBounds
    };

    void startAdvertising( EraseBondsConfig _eraseBonds )noexcept;

    void deleteBonds()noexcept;

private:

    bool m_isConnected;

    /**< Handle of the current connection. */
    std::uint16_t m_connectionHandle;

    /**< Number of peers currently in the whitelist. */
    std::uint32_t m_whiteListPeerCount;

    /**< Device reference handle to the current bonded central. */
    pm_peer_id_t m_peerId;


    ServiceFactory::TBleFactoryPtr m_pServiceCreator;
    std::unique_ptr<Ble::CustomService::CustomService> m_customService;
    Ble::ServiceFactory::IBleServiceFactory::TBatteryServicePtr m_batteryService;
    Ble::ServiceFactory::IBleServiceFactory::TDateTimeServicePtr m_dateTimeService;
    Ble::ServiceFactory::IBleServiceFactory::THeartrateServicePtr m_pHeartrateService;
    using TPeersStorage = std::array<pm_peer_id_t,Ble::Stack::WhiteList::Size>;

    /**< List of peers currently in the whitelist. */
    TPeersStorage m_whitelistPeers;
};

std::unique_ptr<IBleSoftDevice>
createBleStackKeeper( ServiceFactory::TBleFactoryPtr&& _pServiceCreator )noexcept;

};
