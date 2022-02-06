#pragma once

#include "ih_block_device.hpp"

namespace Filesystem::BlockDevice
{
template <typename TFlashDriver>
class SpiFlashBlockDevice : public BlockDeviceEntity<SpiFlashBlockDevice<TFlashDriver>>
{


};

}; // namespace Filesystem::BlockDevice