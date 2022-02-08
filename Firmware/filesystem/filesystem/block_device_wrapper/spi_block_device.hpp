#pragma once

#include "ih_block_device.hpp"

namespace Filesystem::BlockDevice
{
template <typename TFlashDriver>
class SpiFlashBlockDevice : public BlockDeviceEntity<SpiFlashBlockDevice<TFlashDriver>>
{
public:
    constexpr std::uint32_t getBlockSize() const noexcept
    {
        return kBlockSize;
    }
    constexpr std::uint32_t getBlocksCount() const noexcept
    {
        return kSectorsCount;
    }
    constexpr std::uint32_t getReadSize() const noexcept
    {
        return kReadSize;
    }
    constexpr std::uint32_t getProgSize() const noexcept
    {
        return kBlockSize;
    }
    constexpr std::uint32_t getEraseSize() const noexcept
    {
        return kEraseSize;
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
            std::uint32_t highPart = blockAddress / getBlockSize();
            std::uint32_t lowPart = blockAddress % getBlockSize();

            co_await m_currentFlashDriver.pageWrite(_address, std::span(_blockData, _blockSize));

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
            std::uint32_t hi = blockAddress / getBlockSize();
            std::uint32_t lo = blockAddress % getBlockSize();

            auto resultBuffer = co_await m_currentFlashDriver.requestReadBlock();
            memcpy(pReadBuffer, resultBuffer.data(), getReadSize());

            blockAddress += getReadSize();
            pReadBuffer += getReadSize();
            blockSize -= getReadSize();
        }
        co_return;
    }

private:
    static constexpr std::size_t kBlockSize = 256;
    static constexpr std::size_t kSectorsCount = 65'536;
    static constexpr std::size_t kReadSize = 256;
    static constexpr std::size_t kEraseSize = 4096;

private:
    TFlashDriver m_currentFlashDriver;
};

}; // namespace Filesystem::BlockDevice