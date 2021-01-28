#pragma once
#include "ih/drivers/ih_display_idisplay.hpp"

#include "display_spi_common_coro.hpp"

namespace DisplayDriver
{

    class GC9A01Compact
        : public BaseSpiDisplayCoroutine
    {

    public:

        explicit GC9A01Compact(
            std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
            , std::uint16_t _width
            , std::uint16_t _height
        )noexcept;

        ~GC9A01Compact()noexcept override{}

        void turnOn()noexcept override{}

        void turnOff()noexcept override{}

        void fillRectangle(
            std::uint16_t _x
            , std::uint16_t _y
            , std::uint16_t _width
            , std::uint16_t _height
            , IDisplayDriver::TColor* _color
        ) noexcept override;

        void initialize()noexcept override;
    public:

        void initDisplay() noexcept;

        CoroUtils::VoidTask setAddrWindow(
            std::uint16_t _x
            , std::uint16_t _y
            , std::uint16_t _width
            , std::uint16_t _height
        ) noexcept;
    };

    std::unique_ptr<GC9A01Compact>
        createDisplayDriverCompactCoroBasedGC9A01(
            std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
            , std::uint16_t _width
            , std::uint16_t _height
        ) noexcept;

}; // namespace DisplayDriver