#pragma once

#include"ih_block_device.hpp"
#include<etl/vector.h>

namespace Wrapper
{
inline constexpr std::size_t kBlockSize = 512;
inline constexpr std::size_t kSectorsCount = 64;

template<std::size_t BlockSize = kBlockSize, std::size_t SectorsCount = kSectorsCount>
class HeapBlockDevice : public BlockDeviceEntity<HeapBlockDevice<BlockSize,SectorsCount>>
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

private:
    using TBlocksStorage = etl::vector<etl::vector<std::uint8_t, BlockSize>, SectorsCount>;
    TBlocksStorage m_blockStorage;
};
}