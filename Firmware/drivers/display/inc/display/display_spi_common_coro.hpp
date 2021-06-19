#pragma once

#include <gpio/gpio_pin.hpp>

#include <delay/delay_provider.hpp>
#include <spi/spi_wrapper_async_templated.hpp>

#include <utils/CoroUtils.hpp>
#include <utils/SimpleSignal.hpp>

#include <array>
#include <cstdint>
#include <memory>

namespace DisplayDriver
{
template <
    typename TConcreteDisplay,
    typename TSpiBusInstance,
    std::uint16_t Width,
    std::uint16_t Height>
class BaseSpiDisplayCoroutine
{
    using This_t = BaseSpiDisplayCoroutine<TConcreteDisplay, TSpiBusInstance, Width, Height>;

public:
    void turnOn() noexcept
    {
        pOffspring()->turnOn();
    }

    void turnOff() noexcept
    {
        pOffspring()->turnOff();
    }

    using TColor = std::uint16_t;

    void fillRectangle(
        std::uint16_t _x,
        std::uint16_t _y,
        std::uint16_t _width,
        std::uint16_t _height,
        TColor* _color) noexcept
    {
        pOffspring()->fillRectangle(_x, _y, _width, _height, _color);
    }

    void initialize() noexcept
    {
        pOffspring()->initialize();
    };

    bool isInitialized() const noexcept
    {
        return m_displayInitialized.isSet();
    }

    Simple::Signal<void()> onRectArreaFilled;

protected:
    struct Awaiter
    {
        bool resetDcPin = false;
        bool restoreInSpiCtx = false;
        const std::uint8_t* pTransmitBuffer;
        This_t* pBaseDisplay;
        std::uint16_t bufferSize;

        bool await_ready() const noexcept
        {
            const bool isAwaitReady = pTransmitBuffer == nullptr || bufferSize == 0;
            return isAwaitReady;
        }
        void await_resume() const noexcept
        {
            if (resetDcPin)
                pBaseDisplay->setDcPin();
        }
        void await_suspend(std::coroutine_handle<> thisCoroutine) const
        {
            if (resetDcPin)
                pBaseDisplay->resetDcPin();

            pBaseDisplay->getSpiBus()->transmitBuffer(
                pTransmitBuffer, bufferSize, thisCoroutine.address(), restoreInSpiCtx);
        }
    };

    auto sendCommandImpl(const std::uint8_t* _command) noexcept
    {
        return Awaiter{
            .resetDcPin = true,
            .restoreInSpiCtx = false,
            .pTransmitBuffer = _command,
            .pBaseDisplay = this,
            .bufferSize = 1};
    }

    auto sendCommandImplFast(const std::uint8_t* _command) noexcept
    {
        return Awaiter{
            .resetDcPin = true,
            .restoreInSpiCtx = true,
            .pTransmitBuffer = _command,
            .pBaseDisplay = this,
            .bufferSize = 1};
    }

    auto sendChunk(const std::uint8_t* _pBuffer, std::size_t _bufferSize) noexcept
    {
        return Awaiter{
            .pTransmitBuffer = _pBuffer,
            .pBaseDisplay = this,
            .bufferSize = static_cast<std::uint16_t>(_bufferSize)};
    }

    auto sendChunkFast(const std::uint8_t* _pBuffer, std::size_t _bufferSize) noexcept
    {
        return Awaiter{
            .restoreInSpiCtx = true,
            .pTransmitBuffer = _pBuffer,
            .pBaseDisplay = this,
            .bufferSize = static_cast<std::uint16_t>(_bufferSize)};
    }

    auto sendCommand(const std::uint8_t* _pBuffer, std::size_t _bufferSize) noexcept
    {
        const std::uint8_t* commandBuf = _pBuffer;
        const std::uint8_t* ArgBuf = _pBuffer + 1;
        const std::uint16_t ArgsBufferSize = static_cast<std::uint16_t>(_bufferSize - 1);

        return CoroUtils::when_all_sequence(
            sendCommandImpl(commandBuf),
            ArgsBufferSize > 0 ? sendChunk(ArgBuf, ArgsBufferSize) : sendChunk(nullptr, 0));
    }

    auto sendCommandFast(const std::uint8_t* _pBuffer, std::size_t _bufferSize) noexcept
    {
        const std::uint8_t* commandBuf = _pBuffer;
        const std::uint8_t* ArgBuf = _pBuffer + 1;
        const std::uint16_t ArgsBufferSize = static_cast<std::uint16_t>(_bufferSize - 1);

        return CoroUtils::when_all_sequence(
            sendCommandImplFast(commandBuf),
            ArgsBufferSize > 0 ? sendChunk(ArgBuf, ArgsBufferSize) : sendChunk(nullptr, 0));
    }

protected:
    void resetDcPin() noexcept
    {
        m_dcPin.reset();
    }

    void setDcPin() noexcept
    {
        m_dcPin.set();
    }

    void resetResetPin() noexcept
    {
        m_resetPin.reset();
    }

    void setResetPin() noexcept
    {
        m_resetPin.set();
    }

protected:
    constexpr std::uint16_t getWidth() const noexcept
    {
        return m_width;
    }

    constexpr std::uint16_t getHeight() const noexcept
    {
        return m_height;
    }

    auto getSpiBus() noexcept
    {
        return &m_spiBus;
    }

    CoroUtils::Event m_displayInitialized;

    auto pOffspring()
    {
        return static_cast<TConcreteDisplay*>(this);
    }

private:
    const std::uint16_t m_width = Width;
    const std::uint16_t m_height = Height;

    Gpio::DisplayDataCommandPin m_dcPin;
    Gpio::DisplayResetPin m_resetPin;
    TSpiBusInstance m_spiBus;
};

} // namespace DisplayDriver