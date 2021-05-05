#pragma once

#include "ih/drivers/ih_display_idisplay.hpp"

#include <gpio/gpio_pin.hpp>
#include <utils/SimpleSignal.hpp>

#include <memory>
#include <cstdint>

#include <ih/drivers/transaction_item.hpp>

#include <spi/spi_wrapper.hpp>
#include <delay/delay_provider.hpp>

namespace Interface::Spi
{
    class SpiBus;
}

namespace DisplayDriver
{

class BaseSpiDisplay
    :   public IDisplayDriver
{

public:
    BaseSpiDisplay(
            std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
        ,   std::uint16_t _width
        ,   std::uint16_t _height
    )   :   m_width{ _width }
        ,   m_height { _height }
        ,   m_pBusPtr{ std::move( _busPtr ) }
    {

    }

    ~BaseSpiDisplay()noexcept override = default;

protected:

    void sendCommand(
            std::uint8_t _command
    )noexcept
    {
        Interface::Spi::Transaction commandTransaction{};

        commandTransaction.beforeTransaction =
            [ this ]
            {
                resetDcPin();
            };

        commandTransaction.transactionAction =
            [ this, _command ]
            {
                m_pBusPtr->sendData( _command );
            };

        commandTransaction.afterTransaction =
            [ this ]
            {
                setDcPin();
            };

        m_pBusPtr->addTransaction( std::move( commandTransaction ) );
    }

    template< typename ... Args >
    void sendCommand(
            std::uint8_t _command
        ,   Args... _commandArgs
    )noexcept
    {
        sendCommand( _command );
        sendChunk( static_cast<std::uint8_t>(_commandArgs)... );
    }

    template< typename ... Args >
    void sendChunk(
            Args... _chunkArgs
    )noexcept
    {
        std::array chunk = { static_cast<std::uint8_t>(_chunkArgs)... };
        Interface::Spi::Transaction chunkTransaction{};

        chunkTransaction.beforeTransaction =
            [ this ]
            {
                setDcPin();
            };

        chunkTransaction.transactionAction =
            [ this, chunkToSend = std::move( chunk ) ]
            {
                m_pBusPtr->sendChunk(
                        reinterpret_cast<const std::uint8_t*>( chunkToSend.data() )
                    ,   chunkToSend.size()
                );
            };

        chunkTransaction.afterTransaction =
            [ this ]
            {
                resetDcPin();
            };

        m_pBusPtr->addTransaction( std::move( chunkTransaction ) );
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

    Interface::Spi::SpiBus* getSpiBus() noexcept
    {
        return m_pBusPtr.get();
    }

private:

    const std::uint16_t m_width;
    const std::uint16_t m_height;

    Gpio::DisplayDataCommandPin m_dcPin;
    Gpio::DisplayResetPin m_resetPin;
    std::unique_ptr<Interface::Spi::SpiBus> m_pBusPtr;

};

}