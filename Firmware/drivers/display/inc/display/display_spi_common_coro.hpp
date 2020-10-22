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
        bool resetDcPin = false;
        const std::uint8_t* pTransmitBuffer;
        BaseSpiDisplayCoroutine* pBaseDisplay;
        std::uint16_t bufferSize;

        bool await_ready() const noexcept
        {
            return false;
        }
        void await_resume() const noexcept
        {
            if( resetDcPin )
                pBaseDisplay->setDcPin();
        }
        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const
        {
            if (resetDcPin)
                pBaseDisplay->resetDcPin();

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
        auto& pTransmitBuffer = m_pBusPtr->getDmaBufferTransmit();
        pTransmitBuffer[0] = _command;

        return Awaiter
        {
                .resetDcPin = true
            ,   .pTransmitBuffer = pTransmitBuffer.data()
            ,   .pBaseDisplay = this
            ,   .bufferSize = 1
        };
    }

    auto sendChunk(
            const std::uint8_t* _pBuffer
        ,   std::uint16_t _bufferSize
    )noexcept
    {
        return Awaiter
        {
                .pTransmitBuffer = _pBuffer
            ,   .pBaseDisplay = this
            ,   .bufferSize = _bufferSize
        };
    }

    auto sendCommand(
            std::uint8_t _command
        ,   const std::uint8_t* _pBuffer
        ,   std::uint16_t _bufferSize
    )noexcept
    {
        return CoroUtils::when_all (
                sendCommand( _command )
            ,   sendChunk( _pBuffer,_bufferSize )
        );
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