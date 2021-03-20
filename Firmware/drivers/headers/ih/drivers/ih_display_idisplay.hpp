#pragma once

#include "utils/SimpleSignal.hpp"

namespace DisplayDriver
{

class IDisplayDriver
{

public:

    using TColor = std::uint16_t;

    virtual ~IDisplayDriver()noexcept = default;

    virtual void fillRectangle(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
        ,   TColor* _colorToFill
    )noexcept = 0;

    virtual void turnOn()noexcept = 0;

    virtual void turnOff()noexcept = 0;

    virtual void initialize() noexcept {};

    virtual bool isInitialized() const noexcept{ return false;};
    
public:
    Simple::Signal<void()> onRectArreaFilled;

};

} // namespace DisplayDriver
