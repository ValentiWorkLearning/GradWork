#pragma once

#include "ble.h"
#include "ble_srv_common.h"

#include "utils/MetaUtils.hpp"
#include "utils/Noncopyable.hpp"

#include <cstdint>
#include <array>

namespace Ble::CustomService
{
    inline constexpr std::uint8_t UuidSize = 16;

    inline constexpr std::array<std::uint8_t,UuidSize> UuidBase_BE = {
            0xF3, 0x64,0xAD,0xC9
        ,   0xB0, 0x00
        ,   0x40, 0x42
        ,   0xBA, 0x50
        ,   0x05, 0xCA,0x45,0xBF, 0x8A, 0xBC
    };

    inline constexpr std::array CustomServiceUuid{ Meta::reverseArray( UuidBase_BE ) };
    inline constexpr std::uint8_t ServiceType = BLE_UUID_TYPE_VENDOR_BEGIN;

    inline constexpr std::uint16_t ServiceUuid = 0x1400;
    inline constexpr std::uint16_t ValueCharUuid = 0x1401;

    inline constexpr std::uint8_t ServiceObserverPriority = 2;

    class CustomService
        :   private Utils::noncopyable
    {

        public:

        CustomService();
        ~CustomService() = default;

        private:

        void initCustomService()noexcept;

        private:
        using TThis = CustomService;

        static void serviceBleEventHandler( ble_evt_t const * _pEvent, void * _pContext )noexcept;

        void bleEventHandler( ble_evt_t const * _pEvent )noexcept;

        void initEventHandler()noexcept;

        private:

        std::uint16_t m_serviceHandle;
        ble_gatts_char_handles_t m_customValueHandles;   
        std::uint16_t m_connectionHandle;
        std::uint8_t m_uuidType;
    };
}
