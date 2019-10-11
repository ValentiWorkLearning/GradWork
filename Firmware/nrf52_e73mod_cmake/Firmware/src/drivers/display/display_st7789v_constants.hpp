#pragma once

#include <cstdint>

namespace DisplayDriver{


namespace St7789vRegisters
{
    constexpr std::uint8_t TFT_WIDTH_128   = 128;  // for 1.44 and mini
    constexpr std::uint8_t TFT_WIDTH_80    = 80;   // for mini
    constexpr std::uint8_t TFT_HEIGHT_128  = 128;  // for 1.44" display
    constexpr std::uint8_t TFT_HEIGHT_160  = 160;  // for 1.8" and mini display

    constexpr std::uint8_t DELAY      = 0x80;   // special signifier for command lists

    constexpr std::uint8_t NOP        = 0x00;
    constexpr std::uint8_t SWRESET    = 0x01;
    constexpr std::uint8_t RDDID      = 0x04;
    constexpr std::uint8_t RDDST      = 0x09;

    constexpr std::uint8_t SLPIN      = 0x10;
    constexpr std::uint8_t SLPOUT     = 0x11;
    constexpr std::uint8_t PTLON      = 0x12;
    constexpr std::uint8_t NORON      = 0x13;

    constexpr std::uint8_t INVOFF     = 0x20;
    constexpr std::uint8_t INVON      = 0x21;
    constexpr std::uint8_t DISPOFF    = 0x28;
    constexpr std::uint8_t DISPON     = 0x29;
    constexpr std::uint8_t CASET      = 0x2A;
    constexpr std::uint8_t RASET      = 0x2B;
    constexpr std::uint8_t RAMWR      = 0x2C;
    constexpr std::uint8_t RAMRD      = 0x2E;

    constexpr std::uint8_t PTLAR      = 0x30;
    constexpr std::uint8_t TEOFF      = 0x34;
    constexpr std::uint8_t TEON       = 0x35;
    constexpr std::uint8_t MADCTL     = 0x36;
    constexpr std::uint8_t COLMOD     = 0x3A;
    constexpr std::uint8_t MADCTL_MY  = 0x80;
    constexpr std::uint8_t MADCTL_MX  = 0x40;
    constexpr std::uint8_t MADCTL_MV  = 0x20;
    constexpr std::uint8_t MADCTL_ML  = 0x10;
    constexpr std::uint8_t MADCTL_RGB = 0x00;

    constexpr std::uint8_t RDID1      = 0xDA;
    constexpr std::uint8_t RDID2      = 0xDB;
    constexpr std::uint8_t RDID3      = 0xDC;
    constexpr std::uint8_t RDID4      = 0xDD;
};
};

namespace DisplayDriver::Colors
{
    constexpr std::uint32_t BLACK      = 0x0000;
    constexpr std::uint32_t WHITE      = 0xFFFF;
    constexpr std::uint32_t RED        = 0xF800;
    constexpr std::uint32_t GREEN      = 0x07E0;
    constexpr std::uint32_t BLUE       = 0x001F;
    constexpr std::uint32_t CYAN       = 0x07FF;
    constexpr std::uint32_t MAGENTA    = 0xF81F;
    constexpr std::uint32_t YELLOW     = 0xFFE0;
    constexpr std::uint32_t ORANGE     = 0xFC00;
};