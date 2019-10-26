#pragma once

#include "ble.h"
#include "ble_srv_common.h"

#include <cstdint>
#include <array>
#include <bitset>

// #include <arpa/inet.h>

namespace Ble::CustomService
{
    // static constexpr std::array UUID_BE = {
    //         0xCA,0x32,0x44,0xCC
    //     ,   0xF4,0x3A
    //     ,   0x11, 0xE9
    //     ,   0xa7, 0x13
    //     ,   0x2A, 0x2A,0xE2,0xDB, 0xCC, 0xE4
    // };

    static constexpr std::uint8_t UuidSize = 16;

    static constexpr std::array<std::uint8_t,UuidSize> UuidBase_BE = {
            0xF3, 0x64,0xAD,0xC9
        ,   0xB0, 0x00
        ,   0x40, 0x42
        ,   0xBA, 0x50
        ,   0x05, 0xCA,0x45,0xBF, 0x8A, 0xBC
    };


    template<typename TArray>
    constexpr auto reverseByteOrder( TArray _array )
    {   
        TArray outputArray{};
        for( size_t i{}; i< _array.size(); ++i )
        {
            outputArray[ _array.size()-i-1 ] = _array[i];
        }
            
        return outputArray;
    }

    static constexpr std::array UuidBase{
        reverseByteOrder( UuidBase_BE )
    };

    static constexpr std::size_t ServiceUuid = 0x1400;
    static constexpr std::size_t ValueCharUuid = 0x1401;


    class CustomService
    {

        public:
        CustomService();

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

    // struct BleCustomService
    // {
    //     std::uint16_t se
    // };
}
