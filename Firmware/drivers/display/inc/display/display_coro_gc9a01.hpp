#pragma once

#include "ih/drivers/ih_display_idisplay.hpp"

#include "display_spi_common_coro.hpp"

namespace DisplayDriver
{

class GC9A01Coro
        :   public BaseSpiDisplayCoroutine
{

public:

    explicit GC9A01Coro(
            std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    );

    ~GC9A01Coro()noexcept override;

    void turnOn()noexcept override;

    void turnOff()noexcept override;

    void fillRectangle(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
        ,   IDisplayDriver::TColor* _color
    ) noexcept override;

private:

    void initDisplay() noexcept;

    void setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    ) noexcept;
};

std::unique_ptr<GC9A01Coro>
createDisplayDriverCoroBasedGC9A01(
        std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
) noexcept;

}; // namespace DisplayDriver

