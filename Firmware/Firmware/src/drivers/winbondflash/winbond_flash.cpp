#include "winbond_flash.hpp"

#include "spi/transaction_item.hpp"

#include "nrf_delay.h"
#include "pca10040.h"

#include <array>


namespace ExternalFlash
{


WinbondFlash::WinbondFlash(
        Interface::Spi::SpiBus* _busPtr
    )
    :   m_pBusPtr{ _busPtr }
    {    
    }



void
WinbondFlash::requestWriteBlock(
        const std::uint32_t _address
    ,   const std::uint8_t* _blockData
    ,   const std::uint32_t _blockSize
)
{
}

void
WinbondFlash::requestChipErase()
{

}

void
WinbondFlash::requestDeviceId()
{
}

void
WinbondFlash::requestEnterSleepMode()
{

}

void
WinbondFlash::requestRestoreFromSleepMode()
{

};


std::unique_ptr<WinbondFlash>
createFlashDriver(
        Interface::Spi::SpiBus* _busPtr
)
{
    return std::make_unique<WinbondFlash>(
        _busPtr
    );
}

}