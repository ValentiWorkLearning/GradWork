#pragma once
#include <cstdint>

namespace Wrapper
{
template <typename TImpl> class BlockDeviceEntity
{
public:
    constexpr std::uint32_t getBlockSize() const noexcept
    {
        return offspring()->getBlockSize();
    }
    constexpr std::uint32_t getBlocksCount() const noexcept
    {
        return offspring()->getBlocksCount();
    }
    constexpr std::uint32_t getReadSize() const noexcept
    {
        return offspring()->getReadSize();
    }
    constexpr std::uint32_t getProgSize() const noexcept
    {
        return offspring()->getProgSize();
    }
    constexpr std::uint32_t getEraseSize() const noexcept
    {
        return offspring()->getEraseSize();
    }

    constexpr void write(std::uint32_t _address, const std::uint8_t* _blockData, std::uint32_t _blockSize) noexcept
    {
        offspring()->write(_address, _blockData, _blockSize);
    }
    constexpr void read(std::uint8_t* pblockOut, std::uint32_t _address, std::uint32_t _blockSize) noexcept
    {
        offspring()->read(pblockOut, _address, _blockSize);
    }

private:
    constexpr auto offspring()
    {
        return static_cast<TImpl*>(this);
    }
};
} // namespace Wrapper