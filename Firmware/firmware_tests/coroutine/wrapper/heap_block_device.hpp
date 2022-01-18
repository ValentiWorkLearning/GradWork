#pragma once

#include "ih_block_device.hpp"
#include <etl/vector.h>

namespace Wrapper
{
inline constexpr std::size_t kBlockSize = 256;
inline constexpr std::size_t kSectorsCount = 65'536;
inline constexpr std::size_t kReadSize = 256;
inline constexpr std::size_t kEraseSize = 4096;

template <
    std::size_t BlockSize = kBlockSize,
    std::size_t SectorsCount = kSectorsCount,
    std::size_t ReadSize = kReadSize,
    std::size_t EraseSize = kEraseSize,
    std::size_t ProgSize = kReadSize>
class HeapBlockDevice
    : public BlockDeviceEntity<
          HeapBlockDevice<BlockSize, SectorsCount, ReadSize, EraseSize, ProgSize>>
{
public:
    constexpr HeapBlockDevice()
    {
        m_blockStorage.resize(SectorsCount);
        std::ranges::for_each(
            m_blockStorage, [](auto& storageBlock) { std::ranges::fill(storageBlock, 0xFF); });
    }

    constexpr std::uint32_t getBlockSize() const noexcept
    {
        return BlockSize;
    }
    constexpr std::uint32_t getBlocksCount() const noexcept
    {
        return SectorsCount;
    }
    constexpr std::uint32_t getReadSize() const noexcept
    {
        return ReadSize;
    }
    constexpr std::uint32_t getProgSize() const noexcept
    {
        return ProgSize;
    }
    constexpr std::uint32_t getEraseSize() const noexcept
    {
        return EraseSize;
    }

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

            auto& pBlock = m_blockStorage[highPart];
            memcpy(pBlock.data() + lowPart, pBlockRequest, getProgSize());

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

            memcpy(pReadBuffer, m_blockStorage[hi].data() + lo, getReadSize());
            blockAddress += getReadSize();
            pReadBuffer += getReadSize();
            blockSize -= getReadSize();
        }
        co_return;
    }

private:
    static constexpr std::uint32_t kDefRequestSize = 1;

private:
    using TBlocksStorage = std::vector<std::array<std::uint8_t, BlockSize>>;
    TBlocksStorage m_blockStorage;
};
} // namespace Wrapper