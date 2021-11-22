#pragma once
#include <cstdint>

namespace Wrapper
{
class IBlockDeviceEntity
{
public:
    virtual std::uint32_t getBlockSize() const noexcept = 0;
    virtual std::uint32_t getBlocksCount() const noexcept = 0;
};
} // namespace Wrapper