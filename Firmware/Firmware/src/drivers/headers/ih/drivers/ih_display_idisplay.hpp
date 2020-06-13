#pragma once

#include "utils/SimpleSignal.hpp"

namespace DisplayDriver
{

class IDisplayDriver
{

public:

    using TColor = std::uint16_t;

    virtual ~IDisplayDriver() = default;

    virtual void fillRectangle(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
        ,   TColor* _colorToFill
    ) = 0;

    virtual void turnOn() = 0;

    virtual void turnOff() = 0;

public:
    Simple::Signal<void()> onRectArreaFilled;

};

} // namespace DisplayDriver
