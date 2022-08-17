#pragma once

#include "ih_block_device.hpp"

namespace Filesystem::BlockDevice
{

struct FlashBlockDeviceDescriptor
{
    static constexpr inline std::size_t kBlockSize = 256;
    static constexpr inline std::size_t kSectorsCount = 65'536;
    static constexpr inline std::size_t kReadSize = 256;
    static constexpr inline std::size_t kEraseSize = 4096;
};

template <typename TFlashDriver, typename TBlockDeviceDescriptor>

class SpiFlashBlockDevice
    : public BlockDeviceEntity<SpiFlashBlockDevice<TFlashDriver, TBlockDeviceDescriptor>>
{
public:
    constexpr std::uint32_t getBlockSize() const noexcept
    {
        return TBlockDeviceDescriptor::kBlockSize;
    }
    constexpr std::uint32_t getBlocksCount() const noexcept
    {
        return TBlockDeviceDescriptor::kSectorsCount;
    }
    constexpr std::uint32_t getReadSize() const noexcept
    {
        return TBlockDeviceDescriptor::kReadSize;
    }
    constexpr std::uint32_t getProgSize() const noexcept
    {
        return TBlockDeviceDescriptor::kBlockSize;
    }
    constexpr std::uint32_t getEraseSize() const noexcept
    {
        return TBlockDeviceDescriptor::kEraseSize;
    }

public:
    CoroUtils::VoidTask write(
        std::uint32_t _address,
        const std::uint8_t* _blockData,
        std::uint32_t _blockSize) noexcept
    {
        std::uint32_t requestSize = _blockSize;
        const std::uint8_t* pBlockRequest = _blockData;
        std::uint32_t blockAddress{_address};
        while (requestSize > 0)
        {
            co_await m_currentFlashDriver.pageWrite(
                blockAddress, std::span(pBlockRequest, getProgSize()));

            blockAddress += getProgSize();
            pBlockRequest += getProgSize();
            requestSize -= getProgSize();
        }
        co_return;
    }

    CoroUtils::VoidTask read(
        std::uint8_t* _pBlockOut,
        std::uint32_t _address,
        std::uint32_t _blockSize) noexcept
    {
        std::uint32_t blockSize{_blockSize};
        std::uint8_t* pReadBuffer{_pBlockOut};
        std::uint32_t blockAddress{_address};

        while (blockSize > 0)
        {
            auto resultBuffer =
                co_await m_currentFlashDriver.requestReadBlock(blockAddress, getReadSize());
            memcpy(pReadBuffer, resultBuffer.data(), getReadSize());

            blockAddress += getReadSize();
            pReadBuffer += getReadSize();
            blockSize -= getReadSize();
        }
        co_return;
    }

private:
    TFlashDriver m_currentFlashDriver;
};

template <typename DriverBackend>
using SpiBlockDeviceDefaultDevice = SpiFlashBlockDevice<DriverBackend, FlashBlockDeviceDescriptor>;

}; // namespace Filesystem::BlockDevice