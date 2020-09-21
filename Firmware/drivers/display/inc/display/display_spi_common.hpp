#pragma once

#include "ih/drivers/ih_display_idisplay.hpp"

#include "gpio/gpio_pin.hpp"
#include "utils/SimpleSignal.hpp"

#include <memory>
#include <cstdint>

#include "ih/drivers/transaction_item.hpp"

#include "spi/spi_wrapper.hpp"
#include "delay/delay_provider.hpp"

#include "pca10040.h"

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
        ,   m_dcPin { Gpio::getGpioPin( DISP_DC_PIN, Gpio::Direction::Output) }
        ,   m_resetPin { Gpio::getGpioPin( DISP_RST, Gpio::Direction::Output) }
        ,   m_pBusPtr{ std::move( _busPtr ) }
    {

    }

    ~BaseSpiDisplay()override = default;

protected:

    void sendCommand(
            std::uint8_t _command
    )
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
    )
    {
        sendCommand( _command );
        sendChunk( static_cast<std::uint8_t>(_commandArgs)... );
    }

    template< typename ... Args >
    void sendChunk(
            Args... _chunkArgs
    )
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

    void resetDcPin()
    {
        m_dcPin.reset();
    }

    void setDcPin()
    {
        m_dcPin.set();
    }

    void resetResetPin()
    {
        m_resetPin.reset();
    }

    void setResetPin()
    {
        m_resetPin.set();
    }

protected:

    std::uint16_t getWidth() const
    {
        return m_width;
    }

    std::uint16_t getHeight() const
    {
        return m_height;
    }

    Interface::Spi::SpiBus* getSpiBus()
    {
        return m_pBusPtr.get();
    }

private:

    const std::uint16_t m_width;
    const std::uint16_t m_height;

    Gpio::GpioPin m_dcPin;
    Gpio::GpioPin m_resetPin;
    std::unique_ptr<Interface::Spi::SpiBus> m_pBusPtr;

};

}