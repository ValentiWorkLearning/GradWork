#pragma once

#include <cstdint>
#include <cstddef>

#include "FastPimpl.hpp"
#include "Noncopyable.hpp"
#include "Platform.hpp"

namespace Gpio
{

enum class Direction
{
        Input
    ,   Output
};

class GpioPin
    :   private Utils::noncopyable
{

public:

    explicit GpioPin() = delete;

    explicit GpioPin( std::uint16_t _pinNumber, Direction _pinDirection );

    ~GpioPin();

public:

    void set();

    void reset();

private:

    static constexpr inline std::size_t kImplSize = Platform::GpioImplSize;
    static constexpr inline std::size_t kImplAlignment = Platform::GpioImplAlignment;

    class GpioPlatformImpl;
    Utils::FastPimpl<GpioPlatformImpl,kImplSize,kImplAlignment> m_pGpioBackendImpl;

};

GpioPin getGpioPin( std::uint16_t _pinNumber, Gpio::Direction _pinDirection );

};