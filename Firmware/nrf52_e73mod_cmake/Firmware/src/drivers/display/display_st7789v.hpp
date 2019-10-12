#pragma once

#include <memory>

namespace Interface::Spi
{
    class SpiBus;
}

namespace DisplayDriver
{

class St7789V
{

public:
    constexpr explicit St7789V( Interface::Spi::SpiBus* _busPtr );
    ~St7789V() = default;

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

private:

    Interface::Spi::SpiBus* m_pBusPtr;
};

std::unique_ptr<St7789V>
createDisplayDriver();

}; // namespace DisplayDriver

