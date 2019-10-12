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

    template<typename>
    void sendCommand(
            std::uint16_t _command
        ,   bool _withPostDelay = false
    );

    template< typename ... Args >
    void sendCommand(
            std::uint16_t _command
        ,   bool _withPostDelay = false
        ,   Args... _commandArgs
    );

private:

    Interface::Spi::SpiBus* m_pBusPtr;
};

std::unique_ptr<St7789V>
createDisplayDriver();

}; // namespace DisplayDriver

