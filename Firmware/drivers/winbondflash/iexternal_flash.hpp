#pragma once

#include "SimpleSignal.hpp"

#include <cstdint>

namespace ExternalFlash
{

class IFlashStorageDriver
{

public:

    virtual ~IFlashStorageDriver( ) = default;

public:

    virtual void requestWriteBlock(
            const std::uint32_t _address
        ,   const std::uint8_t* _blockData
        ,   const std::uint32_t _blockSize
    ) = 0;

    virtual void requestChipErase() = 0;

    virtual void requestDeviceId() = 0;

    virtual void requestEnterSleepMode() = 0;

    virtual void requestRestoreFromSleepMode() = 0;

public:

    Simple::Signal<void()> onBlockWriteCompleted;
    Simple::Signal<void(std::uint16_t)> onDeviceIdRequestCompleted;

};

} // namespace DisplayDriver
