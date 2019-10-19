#pragma once

#include <memory>
#include <cstdint>

#include "display/display_st7789v_constants.hpp"
#include "display_framebuffer_keeper.hpp"

namespace Interface::Spi
{
    class SpiBus;
}

namespace DisplayDriver
{

class St7789V
{

public:

    explicit St7789V(
            Interface::Spi::SpiBus* _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    );

    ~St7789V() = default;

    void turnOn();

    void turnOff();


    void drawPixel(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   DisplayDriver::Colors _color
    );

    void fillColor( DisplayDriver::Colors _color );


    void fillRectangle(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
        ,   DisplayDriver::Colors _color
    );

private:

    void initDisplay();

    void sendCommand(
            std::uint8_t _command
    );

    template< typename ... Args >
    void sendCommand(
            std::uint8_t _command
        ,   Args... _commandArgs
    );

    template< typename ... Args >
    void sendChunk(
        Args... _commandArgs
    );

    void initColumnRow(
            std::uint16_t _width
        ,   std::uint16_t _height
    );

    void setAddrWindow(
            std::uint16_t _x
        ,   std::uint16_t _y
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    );

private:

    void transmitFrameBuffer();

private:

    void initGpio();

    void resetDcPin();

    void setDcPin();

private:

    std::uint8_t m_columnStart;
    std::uint8_t m_rowStart;

    const std::uint16_t m_width;
    const std::uint16_t m_height;
    
    size_t m_connectionId;
    Interface::Spi::SpiBus* m_pBusPtr;

    std::unique_ptr<FrameBuffer::DisplayBuffer>m_frameBuffer;
};

std::unique_ptr<St7789V>
createDisplayDriver(
        Interface::Spi::SpiBus* _busPtr
    ,   std::uint16_t _width
    ,   std::uint16_t _height
);

}; // namespace DisplayDriver

