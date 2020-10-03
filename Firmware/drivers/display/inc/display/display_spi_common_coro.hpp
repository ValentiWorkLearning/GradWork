#pragma once

#include "ih/drivers/ih_display_idisplay.hpp"

#include "gpio/gpio_pin.hpp"

#include "spi/spi_wrapper_async.hpp"
#include "delay/delay_provider.hpp"

#include "utils/SimpleSignal.hpp"
#include "utils/CoroUtils.hpp"

#include <memory>
#include <cstdint>
#include <array>

namespace Interface::Spi
{
    class SpiBus;
}

namespace DisplayDriver
{

class BaseSpiDisplayCoroutine
    :   public IDisplayDriver
{

public:
    BaseSpiDisplayCoroutine(
            std::unique_ptr<Interface::Spi::SpiBusAsync>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )   :   m_width{ _width }
        ,   m_height { _height }
        ,   m_dcPin { Gpio::getGpioPin( Gpio::Pins::Display_DataCommand, Gpio::Direction::Output) }
        ,   m_resetPin { Gpio::getGpioPin( Gpio::Pins::Display_Reset, Gpio::Direction::Output) }
        ,   m_pBusPtr{ std::move( _busPtr ) }
    {

    }

    ~BaseSpiDisplayCoroutine()noexcept override = default;

protected:

    struct Awaiter
    {
        std::uint8_t* pTransmitBuffer;
        std::uint16_t bufferSize;
        BaseSpiDisplayCoroutine* pBaseDisplay;

        bool await_ready() const noexcept
        {
            return false;
        }
        void await_resume() const noexcept
        {
            pBaseDisplay->setDcPin();
        }
        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const
        {
            pBaseDisplay->getSpiBus()->transmitBuffer(
                    pTransmitBuffer
                ,   bufferSize
                ,   thisCoroutine.address()
            );
        }
    };

    auto sendCommand(
            std::uint8_t _command
    )noexcept
    {
        resetDcPin();
        auto pTransmitBuffer = m_pBusPtr->getDmaBufferTransmit();
        pTransmitBuffer[0] = _command;

        return Awaiter
        {
                .pTransmitBuffer = pTransmitBuffer.data()
            ,   .bufferSize = 1
            ,   .pBaseDisplay = this
        };
    }

    template< typename ... Args >
    auto sendCommand(
            std::uint8_t _command
        ,   Args... _commandArgs
    )noexcept
    {
        return CoroUtils::when_all (
                sendCommand( _command )
            ,   sendChunk( static_cast<std::uint8_t>(_commandArgs)... )
        );
    }

    template< typename ... Args >
    auto sendChunk(
            Args... _chunkArgs
    )noexcept
    {
        std::array chunkArray = std::array{ static_cast<std::uint8_t>(_chunkArgs)... };
        auto pTransmitBuffer = m_pBusPtr->getDmaBufferTransmit();

        constexpr size_t TransmitBufferSize = sizeof...(Args);
        for (size_t i{}; i< TransmitBufferSize; ++i)
        {
            pTransmitBuffer[i] = chunkArray[i];
        }

        return Awaiter
        {
                .pTransmitBuffer = pTransmitBuffer.data()
            ,   .bufferSize = TransmitBufferSize
            ,   .pBaseDisplay = this
        };
    }

protected:

    void resetDcPin()noexcept
    {
        m_dcPin.reset();
    }

    void setDcPin()noexcept
    {
        m_dcPin.set();
    }

    void resetResetPin()noexcept
    {
        m_resetPin.reset();
    }

    void setResetPin()
    {
        m_resetPin.set();
    }

protected:

    std::uint16_t getWidth() const noexcept
    {
        return m_width;
    }

    std::uint16_t getHeight() const noexcept
    {
        return m_height;
    }

    Interface::Spi::SpiBusAsync* getSpiBus() noexcept
    {
        return m_pBusPtr.get();
    }

private:

    const std::uint16_t m_width;
    const std::uint16_t m_height;

    Gpio::GpioPin m_dcPin;
    Gpio::GpioPin m_resetPin;
    std::unique_ptr<Interface::Spi::SpiBusAsync> m_pBusPtr;

};

}