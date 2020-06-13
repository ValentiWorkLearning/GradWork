#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

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

    GpioPin(
            std::uint8_t _pinNumber
        ,   Gpio::Direction _gpioDirection
    );

    ~GpioPin();

public:

    void set();

    void reset();

private:

    static constexpr inline std::size_t kImplSize = Platform::GpioImplSize;
    static constexpr inline std::size_t kImplAlignment = Platform::GpioImplAlignment;

    class GpioBackendImpl;
    Utils::FastPimpl<GpioBackendImpl,kImplSize,kImplAlignment> m_pGpioBackendImpl;
};

GpioPin getGpioPin ( std::uint8_t _pinNumber, Direction _pinDirection );

} // namespace Gpio
