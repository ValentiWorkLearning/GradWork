#pragma once

#include "ih_block_device.hpp"
#include <etl/vector.h>

namespace Wrapper
{
inline constexpr std::size_t kBlockSize = 512;
inline constexpr std::size_t kSectorsCount = 64;

template <std::size_t BlockSize = kBlockSize, std::size_t SectorsCount = kSectorsCount>
class HeapBlockDevice : public BlockDeviceEntity<HeapBlockDevice<BlockSize, SectorsCount>>
{
public:

    HeapBlockDevice()
    {
        m_blockStorage.resize(SectorsCount);
        std::ranges::for_each(m_blockStorage, [](auto& storageBlock) { std::ranges::fill(storageBlock, 0xFF); });
    }

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
        return 256;
    }
    constexpr std::uint32_t getProgSize() const noexcept
    {
        return 256;
    }
    constexpr std::uint32_t getEraseSize() const noexcept
    {
        return BlockSize;
    }

    constexpr void write(
        std::uint32_t _address,
        const std::uint8_t* _blockData, std::size_t _blockSize) noexcept
    {
        std::size_t requestSize = _blockSize;
        const std::uint8_t* pBlockRequest = static_cast<const std::uint8_t*>(_blockData);
        while(requestSize>0)
        {
            std::uint32_t highPart = _address / getEraseSize();
            std::uint32_t lowPart = _address % getEraseSize();
            auto& pBlock = m_blockStorage[highPart];
            memcpy(pBlock.data() + lowPart, pBlockRequest, getProgSize());
            
            pBlockRequest += getProgSize();
            _address += getProgSize();
            requestSize -= getProgSize();
        }
    }
    void read(std::uint8_t* _pBlockOut, std::uint32_t _address, std::uint32_t _blockSize) noexcept
    {
        while (_blockSize > 0)
        {
            std::uint32_t hi = _address / getEraseSize();
            std::uint32_t lo = _address % getEraseSize();

            memcpy(_pBlockOut, m_blockStorage[hi].data() + lo, getReadSize());

            _pBlockOut += getReadSize();
            _address += getReadSize();
            _blockSize -= getReadSize();
        }
    }

private:
    static constexpr std::uint32_t kDefRequestSize = 1;

private:
    using TBlocksStorage = std::vector<std::array<std::uint8_t, BlockSize>>;
    TBlocksStorage m_blockStorage;
};
} // namespace Wrapper