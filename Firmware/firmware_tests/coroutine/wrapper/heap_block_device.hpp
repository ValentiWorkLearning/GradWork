#pragma once

#include"ih_block_device.hpp"
#include<etl/vector.h>

namespace Wrapper
{
inline constexpr std::size_t kBlockSize = 512;
inline constexpr std::size_t kSectorsCount = 64;

template<std::size_t BlockSize = kBlockSize, std::size_t SectorsCount = kSectorsCount>
class HeapBlockDevice : public BlockDeviceEntity<HeapBlockDevice<BlockSize, SectorsCount>>
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
    constexpr void write(
        const std::uint32_t _address,
        std::span<const std::uint8_t> _blockData) noexcept
    {
        std::uint32_t highPart = _address / kBlockSize;
        std::uint32_t lowPart = _address % kBlockSize;
        auto& pBlock = m_blockStorage[highPart];
        memcpy(pBlock.data() + lowPart, _blockData.data(), _blockData.size());
    }

private:
    using TBlocksStorage = etl::array<etl::array<std::uint8_t, BlockSize>, SectorsCount>;
    TBlocksStorage m_blockStorage;
};
}