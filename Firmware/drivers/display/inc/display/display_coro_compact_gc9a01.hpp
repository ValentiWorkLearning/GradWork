#pragma once

#include "display_spi_common_coro.hpp"

namespace DisplayDriver::InitializationCommands
{
// clang-format off
constexpr std::size_t CommandsSize = 328;
constexpr std::size_t CommandsTransactionsCount = 59;
static auto Commands = std::array<std::uint8_t, CommandsSize>
{
    /***Cmd****Argc****delay****argv*****************************/
        0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14

    ,   0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14
    ,   0xFE,   0,      0
    ,   0xEF,   0,      0
    ,   0xEB,   1,      0,      0x14

    ,   0xFE,   0,      0
    ,   0xEF,   0,      0

    ,   0x84,   1,      0,      0x40
    ,   0x85,   1,      0,      0xF1
    ,   0x86,   1,      0,      0x98
    ,   0x87,   1,      0,      0x28
    ,   0x88,   1,      0,      0x0A
    ,   0x89,   1,      0,      0x21

    ,   0x8A,   1,      0,      0x00
    ,   0x8B,   1,      0,      0x80
    ,   0x8C,   1,      0,      0x01
    ,   0x8D,   1,      0,      0x00
    ,   0x8E,   1,      0,      0xDF
    ,   0x8F,   1,      0,      0x52

    ,   0xB6,   1,      0,      0x20

    ,   0x36,   1,      0,      0x48

    ,   0x3A,   1,      0,      0x05

    ,   0x90,   4,      0,      0x08,0x08,0x08,0x08

    ,   0xBD,   1,      0,      0x06
    ,   0xA6,   1,      0,      0x74
    ,   0xBF,   1,      0,      0x1C
    ,   0xA7,   1,      0,      0x45
    ,   0xA9,   1,      0,      0xBB
    ,   0xB8,   1,      0,      0x63
    ,   0xE8,   1,      0,      0x34

    ,   0xFF,   3,      0,      0x60, 0x01,0x04

    ,   0x74,   7,      0,      0x10,0x75,0x80,0x00,0x00,0x4E,0x00
    ,   0xC3,   5,      0,      0x14,0xC4,0x14,0xC9,0x25

    ,   0xBE,   1,      0,      0x11
    ,   0xBC,   1,      0,      0x00
    ,   0xE1,   2,      0,      0x10,0x0e

    ,   0xDF,   3,      0,      0x21,0x0c,0x02

    ,   0xED,   2,      0,      0x1B,0x0B

    ,   0xAE,   5,      0,      0x77,0xCB,0x02,0xCD,0x63

    ,   0x70,   9,      0,      0x07,0x09,0x04,0x0e,0x0f, 0x09,0x07,0x08,0x03
    ,   0xf0,   6,      0,      0x45,0x09,0x08,0x08,0x26,0x2a
    ,   0xf1,   6,      0,      0x43,0x70,0x72,0x36,0x37,0x6f
    ,   0xf2,   6,      0,      0x45,0x09,0x08,0x08,0x26,0x2a
    ,   0xf3,   6,      0,      0x43,0x70,0x72,0x36,0x37,0x6f

    ,   0x62,   12,     0,      0x18,0x0d,0x71,0xED,0x70,0x70,0x18,0x0F,0x71,0xEF,0x70,0x70
    ,   0x63,   12,     0,      0x18,0x11,0x71,0xf1,0x70,0x70,0x18,0x13,0x71,0xf3,0x70,0x70
    ,   0x64,   7,      0,      0x28,0x29,0xF1,0x01,0xf1,0x00,0x07
    ,   0x66,   10,     0,      0x3c,0x00,0xCD,0x67,0x45,0x45,0x10,0x00,0x00,0x00
    ,   0x67,   10,     0,      0x00,0x3c,0x00,0x00,0x00,0x01,0x54,0x10,0x32,0x98
    ,   0x74,   7,      0,      0x10,0x85,0x80,0x00,0x00,0x4e,0x00

    ,   0x98,   2,      0,      0x3e,0x07

    ,   0x35,   0,      0
    ,   0x21,   0,      0

    ,   0x11,   0,      120
    ,   0x29,   0,      120
};
// clang-format on
} // namespace DisplayDriver::InitializationCommands

namespace DisplayDriver
{
template <typename TSpiBusInstance, std::uint16_t Width, std::uint16_t Height>
class GC9A01Compact
    : public BaseSpiDisplayCoroutine<
          GC9A01Compact<TSpiBusInstance, Width, Height>,
          TSpiBusInstance,
          Width,
          Height>
{
    using TBaseSpiDisplay = BaseSpiDisplayCoroutine<
        GC9A01Compact<TSpiBusInstance, Width, Height>,
        TSpiBusInstance,
        Width,
        Height>;

public:
    void turnOn() noexcept
    {
    }

    void turnOff() noexcept
    {
    }

    void fillRectangle(
        std::uint16_t _x,
        std::uint16_t _y,
        std::uint16_t _width,
        std::uint16_t _height,
        TBaseSpiDisplay::TColor* _colorToFill) noexcept
    {

        const std::uint16_t DisplayHeight = TBaseSpiDisplay::getHeight();
        const std::uint16_t DisplayWidth = TBaseSpiDisplay::getWidth();

        const bool isCoordsValid{!((_x >= DisplayWidth) || (_y >= DisplayHeight))};
        if (isCoordsValid)
        {
            if (_width >= DisplayWidth)
                _width = DisplayWidth - _x;
            if (_height >= DisplayHeight)
                _height = DisplayHeight - _y;

            const size_t BytesSizeX = (_width - _x + 1);
            const size_t BytesSizeY = (_height - _y + 1);
            const size_t BytesSquare = BytesSizeX * BytesSizeY;
            const size_t TransferBufferSize
                = (BytesSquare * sizeof(typename TBaseSpiDisplay::TColor));

            co_await TBaseSpiDisplay::m_displayInitialized;

            co_await setAddrWindow(_x, _y, _width, _height);

            static std::uint8_t RamWriteCmd{0x2C};

            co_await TBaseSpiDisplay::sendCommandImplFast(&RamWriteCmd);

            TBaseSpiDisplay::setDcPin();
            co_await TBaseSpiDisplay::sendChunk(
                reinterpret_cast<const std::uint8_t*>(_colorToFill), TransferBufferSize);
            TBaseSpiDisplay::resetDcPin();

            TBaseSpiDisplay::onRectArreaFilled.emitLater();
        }
    }

    void initialize() noexcept
    {
        initDisplay();
    }

public:
    void initDisplay() noexcept
    {
        TBaseSpiDisplay::resetResetPin();
        Delay::waitFor(100);
        TBaseSpiDisplay::setResetPin();
        size_t CommandCount = InitializationCommands::CommandsTransactionsCount;
        const std::uint8_t* pBuffer = InitializationCommands::Commands.data();
        while (CommandCount--)
        {
            const std::uint8_t* Command = pBuffer++;
            const std::uint8_t NumArgs = *pBuffer++;
            const std::uint8_t Delay = *pBuffer++;

            co_await TBaseSpiDisplay::sendCommandImpl(Command);
            if (NumArgs)
            {
                co_await TBaseSpiDisplay::sendChunk(pBuffer++, NumArgs);
                pBuffer += (NumArgs - 1);
            }
            if (Delay)
                Delay::waitFor(Delay);
        }
        TBaseSpiDisplay::m_displayInitialized.set();
    }

    CoroUtils::VoidTask setAddrWindow(
        std::uint16_t _x,
        std::uint16_t _y,
        std::uint16_t _width,
        std::uint16_t _height) noexcept
    {
        // TODO be careful here;
        std::uint16_t width = _width - _x;
        std::uint16_t height = _height - _y;

        std::uint16_t correctedX = _x;
        std::uint16_t correctedY = _y;

        std::uint32_t xa = (static_cast<std::uint32_t>(correctedX << 16)) | (correctedX + width);
        std::uint32_t ya = (static_cast<std::uint32_t>(correctedY << 16)) | (correctedY + height);

        using TCommandsArray = std::array<std::uint8_t, 5>;
        static TCommandsArray xAxisCommand{};
        xAxisCommand[0] = static_cast<std::uint8_t>(0x2a);
        xAxisCommand[1] = static_cast<std::uint8_t>(xa >> 24);
        xAxisCommand[2] = static_cast<std::uint8_t>(xa >> 16);
        xAxisCommand[3] = static_cast<std::uint8_t>(xa >> 8);
        xAxisCommand[4] = static_cast<std::uint8_t>(xa);

        static TCommandsArray yAxisCommand{};
        yAxisCommand[0] = static_cast<std::uint8_t>(0x2b);
        yAxisCommand[1] = static_cast<std::uint8_t>(ya >> 24);
        yAxisCommand[2] = static_cast<std::uint8_t>(ya >> 16);
        yAxisCommand[3] = static_cast<std::uint8_t>(ya >> 8);
        yAxisCommand[4] = static_cast<std::uint8_t>(ya);

        co_await CoroUtils::when_all_sequence(
            TBaseSpiDisplay::sendCommandFast(xAxisCommand.data(), xAxisCommand.size()),
            TBaseSpiDisplay::sendCommandFast(yAxisCommand.data(), yAxisCommand.size()));
    }
};
}; // namespace DisplayDriver