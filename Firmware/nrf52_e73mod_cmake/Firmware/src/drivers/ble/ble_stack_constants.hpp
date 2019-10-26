#pragma once
#include <cstdint>

namespace Ble::Stack::StackConstants
{
    constexpr std::uint8_t  AppBleConnCfgTag = 1;            /**< A tag identifying the SoftDevice BLE configuration. */
    constexpr std::uint8_t  ObserverPriority = 3;            /**< Application's BLE observer priority. You shouldn't need to modify this value. */
    constexpr std::uint16_t AdvertismentDuration = 1800;    /**< The advertising duration (180 seconds) in units of 10 milliseconds. */
}