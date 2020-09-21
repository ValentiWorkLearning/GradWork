#pragma once

#include "ih/drivers/ih_display_idisplay.hpp"

#include "display_spi_common.hpp"

#include "display_st7789v_constants.hpp"

namespace DisplayDriver
{

class St7789V
        :   public BaseSpiDisplay
{

public:

    explicit St7789V(
            std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    );

    ~St7789V()noexcept override;

    void turnOn()noexcept override;

    void turnOff()noexcept override;

    void fillRectangle(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
        ,   IDisplayDriver::TColor* _color
    )noexcept override;

private:

    void initDisplay()noexcept;

    void initColumnRow(
            std::uint16_t _width
        ,   std::uint16_t _height
    )noexcept;

    void setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )noexcept;

private:

    std::uint8_t m_columnStart;
    std::uint8_t m_rowStart;
};

std::unique_ptr<St7789V>
createDisplayDriverSt7789V(
        std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
)noexcept;

}; // namespace DisplayDriver

