#pragma once

#include <cstddef>

#include "FastPimpl.hpp"
#include "Platform.hpp"

namespace Gpio
{

enum class Direction
{
        Input
    ,   Output
};

class GpioPin
{

public:

    explicit GpioPin(
            std::uint8_t _pinNumber
        ,   Gpio::Direction _gpioDirection
    );

    ~GpioPin() = default;

public:

    void set();

    void reset();

private:

    static constexpr inline std::size_t kImplSize = Platform::GpioImplSize;
    static constexpr inline std::size_t kImplAlignment = Platform::GpioImplAlignment;

    class GpioBackendImpl;
    Utils::FastPimpl<GpioBackendImpl,kImplSize,kImplAlignment> m_pGpioBackendImpl;
};

} // namespace Gpio
