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

    void write(const std::uint32_t _address, std::span<const std::uint8_t> _blockData) noexcept
    {
        return offspring()->write(_address, _blockData);
    }

private:
    constexpr auto offspring()
    {
        return static_cast<TImpl*>(this);
    }
};
} // namespace Wrapper