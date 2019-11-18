#pragma once

#include "ble.h"
#include "ble_srv_common.h"

#include "MetaUtils.hpp"

#include <cstdint>
#include <array>

#include "Noncopyable.hpp"

namespace Ble::CustomService
{
    static constexpr std::uint8_t UuidSize = 16;

    static constexpr std::array<std::uint8_t,UuidSize> UuidBase_BE = {
            0xF3, 0x64,0xAD,0xC9
        ,   0xB0, 0x00
        ,   0x40, 0x42
        ,   0xBA, 0x50
        ,   0x05, 0xCA,0x45,0xBF, 0x8A, 0xBC
    };

    static constexpr std::array CustomServiceUuid{ Meta::reverseArray( UuidBase_BE ) };
    static constexpr std::uint8_t ServiceType = BLE_UUID_TYPE_VENDOR_BEGIN;

    static constexpr std::uint16_t ServiceUuid = 0x1400;
    static constexpr std::uint16_t ValueCharUuid = 0x1401;


    class CustomService
        :   private Utils::noncopyable
    {

        public:

        CustomService();
        ~CustomService() = default;

        private:

        void initCustomService();

        void initAdvertisment();

        void initCustomCharacteric();

        private:

        std::uint16_t m_serviceHandle;

        ble_gatts_char_handles_t m_customValueHandles;   

        std::uint16_t m_connectionHandle;

        std::uint8_t m_uuidType;
    };
}
