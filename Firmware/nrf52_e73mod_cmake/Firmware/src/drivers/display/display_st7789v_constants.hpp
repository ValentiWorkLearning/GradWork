#pragma once

#include <cstdint>
#include <cstddef>

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

namespace DisplayDriver
{
    enum class Colors
    {
            BLACK      = 0x0000
        ,   WHITE      = 0xFFFF
        ,   RED        = 0xF800
        ,   GREEN      = 0x07E0
        ,   BLUE       = 0x001F
        ,   CYAN       = 0x07FF
        ,   MAGENTA    = 0xF81F
        ,   YELLOW     = 0xFFE0
        ,   ORANGE     = 0xFC00
    };

    enum class EncodedColor : unsigned char
    {
            BlackEnc = 0
        ,   WhiteEnc = 1
        ,   RedEnc = 2
        ,   GreenEnc = 3
        ,   BlueEnc = 4
        ,   CyanEnc = 5
        ,   MagentaEnc = 6
        ,   YellowEnc = 7
        ,   OrangeEnc = 8
    };

    inline EncodedColor toEncodedColor( Colors _color )
    {
        switch ( _color )
        {
        case Colors::BLACK:
            return EncodedColor::BlackEnc;
        case Colors::WHITE:
            return EncodedColor::WhiteEnc;
        case Colors::RED:
            return EncodedColor::RedEnc;
        case Colors::GREEN:
            return EncodedColor::GreenEnc;
        case Colors::BLUE:
            return EncodedColor::BlueEnc;
        case Colors::CYAN:
            return EncodedColor::CyanEnc;
        case Colors::MAGENTA:
            return EncodedColor::MagentaEnc;
        case Colors::YELLOW:
            return EncodedColor::YellowEnc;
        case Colors::ORANGE:
            return EncodedColor::OrangeEnc;
        default:
            return EncodedColor::BlackEnc;
            break;
        }
    }
    inline Colors fromEncodedColor( EncodedColor _color )
    {
        switch ( _color )
        {
        case EncodedColor::RedEnc:
            return Colors::RED;
            break;
        case EncodedColor::GreenEnc:
            return Colors::GREEN;
        default:
            return Colors::BLACK;
            break;
        }
    }

};
namespace DisplayDriver::St7789v::Disp208_240
{
    constexpr std::uint8_t Width = 240;
    constexpr std::uint8_t Height = 240;
}

namespace DisplayDriver::St7789v::Disp240_320
{
    constexpr std::uint8_t Width = 240;
    constexpr std::uint16_t Height = 320;
}