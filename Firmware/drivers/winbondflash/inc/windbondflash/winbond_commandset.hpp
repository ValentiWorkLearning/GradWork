#pragma once

#include <cstdint>

namespace WindbondCommandSet::Masks
{
inline constexpr std::uint8_t EraseWriteInProgress = 1 << 0;
}
namespace WindbondCommandSet
{
inline constexpr std::uint8_t WriteEnable = 0x06;
inline constexpr std::uint8_t WriteDisable = 0x04;

inline constexpr std::uint8_t ReadStatusRegister1 = 0x05;
inline constexpr std::uint8_t ReadStatusRegister2 = 0x35;
inline constexpr std::uint8_t ReadStatusRegister3 = 0x15;

inline constexpr std::uint8_t WriteStatusRegister = 0x01;

inline constexpr std::uint8_t ReadData = 0x03;
inline constexpr std::uint8_t FastRead = 0x0b;
inline constexpr std::uint8_t PageProgram = 0x02;

inline constexpr std::uint8_t SectorErase4KB = 0x20;
inline constexpr std::uint8_t BlockErase32KB = 0x52;
inline constexpr std::uint8_t BlockErase64KB = 0xd8;

inline constexpr std::uint8_t ChipErase = 0xc7;
inline constexpr std::uint8_t ChipEraseSimilar = 0x60;

inline constexpr std::uint8_t EraseSuspend = 0x75;
inline constexpr std::uint8_t EraseResume = 0x7A;

inline constexpr std::uint8_t PowerDownMode = 0xb9;
inline constexpr std::uint8_t ResumePowerDownMode = 0xab;

inline constexpr std::uint8_t DeviceIdFromPowedDownRelease = 0xab;
inline constexpr std::uint8_t ReadManufactureId = 0x90;

inline constexpr std::uint8_t JedecIdLength = 3;
inline constexpr std::uint8_t ReadJedecId = 0x9F;

inline constexpr std::uint8_t UniqueIdLength = 8; // 64 bits
inline constexpr std::uint8_t ReadUniqueId = 0x4B;

inline constexpr std::uint8_t DummyByte = 0x00;
} // namespace WindbondCommandSet
