#pragma once

#include "utils/SimpleSignal.hpp"

#include <cstdint>
#include <memory>
#include <array>

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

    static constexpr inline std::uint8_t DeviceIdLength = 8;
    using TDeviceIdType = std::array<std::uint8_t,DeviceIdLength>;
    virtual const TDeviceIdType& getDeviceUniqueId() = 0;

public:

    Simple::Signal<void()> onBlockWriteCompleted;
    Simple::Signal<void()> onRequestDeviceIdCompleted;

};

using TFlashDevicePtr = std::unique_ptr<IFlashStorageDriver>;

} // namespace ExternalFlash
