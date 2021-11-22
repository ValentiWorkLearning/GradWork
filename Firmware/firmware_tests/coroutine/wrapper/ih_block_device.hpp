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

private:
    constexpr auto offspring()
    {
        return static_cast<TImpl*>(this);
    }
};
} // namespace Wrapper