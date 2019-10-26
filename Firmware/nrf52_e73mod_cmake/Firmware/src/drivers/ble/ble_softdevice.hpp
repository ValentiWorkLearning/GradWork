#pragma once

#include <ble.h>
#include "Noncopyable.hpp"

#include <memory>

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

namespace Ble::Stack
{


class BleStackKeeper
    :   private Utils::noncopyable
{

public:

    BleStackKeeper();
    ~BleStackKeeper() = default;

private:

    void bleStackInit();

    void bleEventHandler( ble_evt_t const* _pBleEvent, void * _pContext );

    void initGattModule();

private:

    // Thanks godbolt compiler exporer for this magic-macro expanding.
    // Just add -E compilation flag for getting the post-prreprocessing output

    /**< Context for the Queued Write module.*/
    static nrf_ble_qwr_t m_qwr;
    static constexpr nrf_sdh_ble_evt_observer_t m_qwr_obs __attribute__ ((section("." STRINGIFY(sdh_ble_observersNRF_BLE_QWR_BLE_OBSERVER_PRIO)))) __attribute__((used)) = { .handler = nrf_ble_qwr_on_ble_evt, .p_context = &m_qwr };
    /**< Context for the Queued Write module.*/

    std::uint16_t m_connectionHandle;
};

std::unique_ptr<BleStackKeeper> createBleStackKeeper();

};