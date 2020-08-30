#pragma once

#include <cstdint>


namespace WindbondCommandSet
{
    constexpr std::uint8_t WriteEnable = 0x06;
    constexpr std::uint8_t WriteDisable = 0x04;

    constexpr std::uint8_t ReadStatusRegister1 = 0x05;
    constexpr std::uint8_t ReadStatusRegister2 = 0x35;

    constexpr std::uint8_t WriteStatusRegister = 0x01;

    constexpr std::uint8_t ReadData = 0x03;
    constexpr std::uint8_t FastRead = 0x0b;
    constexpr std::uint8_t PageProgram = 0x02;

    constexpr std::uint8_t SectorErase4KB = 0x20;
    constexpr std::uint8_t BlockErase32KB = 0x52;
    constexpr std::uint8_t BlockErase64KB = 0xd8;

    constexpr std::uint8_t ChipErase = 0xc7; 
    constexpr std::uint8_t ChipEraseSimilar = 0x60;

    constexpr std::uint8_t EraseSuspend = 0x75;
    constexpr std::uint8_t EraseResume = 0x7A;

    constexpr std::uint8_t PowerDownMode = 0xb9;
    constexpr std::uint8_t ResumePowerDownMode = 0xab;

    constexpr std::uint8_t DeviceIdFromPowedDownRelease = 0xab;
    constexpr std::uint8_t ReadManufactureId = 0x90;
    constexpr std::uint8_t ReadJedecId = 0x9F;

    constexpr std::uint8_t UniqueIdLength = 8; // 64 bits
    constexpr std::uint8_t ReadUniqueId = 0x4B;

    constexpr std::uint8_t DummyByte = 0x00;
}
