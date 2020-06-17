#pragma once

#include <cstdint>
#include <string_view>
#include <chrono>

namespace Ble::Stack::StackConstants
{
    constexpr std::uint8_t  AppBleConnCfgTag = 1;            /**< A tag identifying the SoftDevice BLE configuration. */
    constexpr std::uint8_t  ObserverPriority = 3;            /**< Application's BLE observer priority. You shouldn't need to modify this value. */
}

namespace Ble::Stack::SecurityParams
{
    constexpr std::uint8_t Bonding                  = 1;                                       /**< Perform bonding. */
    constexpr std::uint8_t ManInTheMiddle           = 0;                                       /**< Man In The Middle protection not required. */
    constexpr std::uint8_t LeSecureConnections      = 0;                                       /**< LE Secure Connections not enabled. */
    constexpr std::uint8_t KeypressNotifications    = 0;                                       /**< Keypress notifications not enabled. */
    constexpr std::uint8_t IoCapabilities           = BLE_GAP_IO_CAPS_NONE;                    /**< No I/O capabilities. */
    constexpr std::uint8_t OutOfBand                = 0;                                       /**< Out Of Band data not available. */
    constexpr std::uint8_t MinKeySize               = 7;                                       /**< Minimum encryption key size. */
    constexpr std::uint8_t MaxKeySize               = 16;                                      /**< Maximum encryption key size. */
} // namespace Ble::Stack::SecurityConstants

namespace Ble::Stack::GapSettings
{
    constexpr size_t MinConnectionInterval          = MSEC_TO_UNITS( 400, UNIT_1_25_MS );      /**< Minimum acceptable connection interval (0.4 seconds). */
    constexpr size_t MaxConnectionInterval          = MSEC_TO_UNITS( 650, UNIT_1_25_MS );      /**< Maximum acceptable connection interval (0.65 second). */
    constexpr size_t SlaveLatency                   = 0;                                       /**< Slave latency. */
    constexpr size_t ConnectionSupervisoryTimeout   = MSEC_TO_UNITS( 4000, UNIT_10_MS );       /**< Connection supervisory timeout (4 seconds). */

    static std::string_view DeviceName = "VDev";
}

namespace Ble::Stack::AdvertisingSettings
{
    using namespace std::chrono_literals;

    constexpr std::chrono::milliseconds Duration = 18'000ms;
    constexpr std::chrono::milliseconds Interval = 300ms;
}


namespace Ble::Stack::ConnectionParams
{
    constexpr std::uint32_t FirstConnectionParamsUpdateDelay = APP_TIMER_TICKS(5000);                              /**< Time from initiating event (connect or start of notification) to first time sd_ble_gap_conn_param_update is called (5 seconds). */
    constexpr std::uint32_t NextConnectionParamsUpdateDelay = APP_TIMER_TICKS(30000);                              /**< Time between each call to sd_ble_gap_conn_param_update after the first call (30 seconds). */
    constexpr std::uint8_t  MaxConnectionParamsUpdateCount = 3;                                                    /**< Number of attempts before giving up the connection parameter negotiation. */
}

namespace Ble::Stack::WhiteList
{
    constexpr std::uint32_t Size = BLE_GAP_WHITELIST_ADDR_MAX_COUNT;
}