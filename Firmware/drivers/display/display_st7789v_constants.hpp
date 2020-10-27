#pragma once

#include <cstdint>
#include <cstddef>

namespace DisplayDriver{


namespace St7789vRegisters
{
    inline constexpr std::uint8_t TFT_WIDTH_128   = 128;  // for 1.44 and mini
    inline constexpr std::uint8_t TFT_WIDTH_80    = 80;   // for mini
    inline constexpr std::uint8_t TFT_HEIGHT_128  = 128;  // for 1.44" display
    inline constexpr std::uint8_t TFT_HEIGHT_160  = 160;  // for 1.8" and mini display

    inline constexpr std::uint8_t DELAY      = 0x80;   // special signifier for command lists

    inline constexpr std::uint8_t NOP        = 0x00;
    inline constexpr std::uint8_t SWRESET    = 0x01;
    inline constexpr std::uint8_t RDDID      = 0x04;
    inline constexpr std::uint8_t RDDST      = 0x09;

    inline constexpr std::uint8_t SLPIN      = 0x10;
    inline constexpr std::uint8_t SLPOUT     = 0x11;
    inline constexpr std::uint8_t PTLON      = 0x12;
    inline constexpr std::uint8_t NORON      = 0x13;

    inline constexpr std::uint8_t INVOFF     = 0x20;
    inline constexpr std::uint8_t INVON      = 0x21;
    inline constexpr std::uint8_t DISPOFF    = 0x28;
    inline constexpr std::uint8_t DISPON     = 0x29;
    inline constexpr std::uint8_t CASET      = 0x2A;
    inline constexpr std::uint8_t RASET      = 0x2B;
    inline constexpr std::uint8_t RAMWR      = 0x2C;
    inline constexpr std::uint8_t RAMRD      = 0x2E;

    inline constexpr std::uint8_t PTLAR      = 0x30;
    inline constexpr std::uint8_t TEOFF      = 0x34;
    inline constexpr std::uint8_t TEON       = 0x35;
    inline constexpr std::uint8_t MADCTL     = 0x36;
    inline constexpr std::uint8_t COLMOD     = 0x3A;
    inline constexpr std::uint8_t MADCTL_MY  = 0x80;
    inline constexpr std::uint8_t MADCTL_MX  = 0x40;
    inline constexpr std::uint8_t MADCTL_MV  = 0x20;
    inline constexpr std::uint8_t MADCTL_ML  = 0x10;
    inline constexpr std::uint8_t MADCTL_RGB = 0x00;

    inline constexpr std::uint8_t RDID1      = 0xDA;
    inline constexpr std::uint8_t RDID2      = 0xDB;
    inline constexpr std::uint8_t RDID3      = 0xDC;
    inline constexpr std::uint8_t RDID4      = 0xDD;
};
};

namespace DisplayDriver::St7789v::Disp208_240
{
    inline constexpr std::uint8_t Width = 240;
    inline constexpr std::uint8_t Height = 240;
}

namespace DisplayDriver::St7789v::Disp240_320
{
    inline constexpr std::uint8_t Width = 240;
    inline constexpr std::uint16_t Height = 320;
}