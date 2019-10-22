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

    static constexpr std::array<std::uint8_t,UuidSize> UUID_BE = {
            0xF3, 0x64,0xAD,0xC9
        ,   0xB0, 0x00
        ,   0x40, 0x42
        ,   0xBA, 0x50
        ,   0x05, 0xCA,0x45,0xBF, 0x8A, 0xBC
    };


    template<typename TArray>
    auto bigEndianToLittleEndian( TArray _array )
    {   
        constexpr std::uint8_t TItemSize =  sizeof( _array[0] );
        constexpr std::uint8_t BitsInByte = 8;
        constexpr std::uint8_t TItemBitSize = TItemSize * BitsInByte;

        TArray outputArray{};
        for( size_t i{}; i< _array.size(); ++i )
        {
            std::uint8_t lsbValue{};
            for( int j{}; j<TItemBitSize ; ++j )
            {
                bool bitValue = ((_array[i] & (1<<i)) >> i);
                lsbValue |= (bitValue << (TItemBitSize - 1 - i ) );
            }
            outputArray[i] = lsbValue;
        }
            
        return outputArray;
    }

    // static constexpr std::array UUID_LE{
    //     bigEndianToLittleEndian( UUID_BE )
    // };
}
