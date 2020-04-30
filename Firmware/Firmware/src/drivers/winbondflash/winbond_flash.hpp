#pragma once


#include <memory>
#include <cstdint>

#include "iexternal_flash.hpp"
#include "winbond_flash.hpp"

#include "spi/spi_wrapper.hpp"

#include "SimpleSignal.hpp"


namespace Interface::Spi
{
    class SpiBus;
}

namespace ExternalFlash
{

class WinbondFlash
        :   public IFlashStorageDriver
{

public:

    explicit WinbondFlash(
        Interface::Spi::SpiBus* _busPtr
    );

    ~WinbondFlash()override = default;

public:

    void requestWriteBlock(
            const std::uint32_t _address
        ,   const std::uint8_t* _blockData
        ,   const std::uint32_t _blockSize
    )override;

    void requestChipErase() override;

    void requestDeviceId() override;

    void requestEnterSleepMode() override;

    void requestRestoreFromSleepMode() override;

private:

    Interface::Spi::SpiBus* m_pBusPtr;

};

std::unique_ptr<WinbondFlash>
createFlashDriver(
        Interface::Spi::SpiBus* _busPtr
);

}
