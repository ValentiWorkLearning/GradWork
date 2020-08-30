#include "inc/windbondflash/winbond_flash.hpp"
#include "inc/windbondflash/winbond_commandset.hpp"

#include "ih/drivers/transaction_item.hpp"

#include "nrf_delay.h"
#include "pca10040.h"

#include <array>

namespace ExternalFlash
{


WinbondFlash::WinbondFlash(
        std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
    )
    :   m_pBusPtr{ std::move( _busPtr ) }
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
    Interface::Spi::Transaction chipEraseTransaction = writeTransaction(
            WindbondCommandSet::ChipErase
    );
    m_pBusPtr->addTransaction( std::move( chipEraseTransaction ) );
    m_pBusPtr->runQueue();
}

void
WinbondFlash::requestDeviceId()
{
    Interface::Spi::Transaction requestIdCommandTransaction = writeTransaction(
            WindbondCommandSet::ReadUniqueId
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
    );
    m_pBusPtr->addTransaction( std::move( requestIdCommandTransaction ) );


    Interface::Spi::Transaction receiveDataTranscation =
        readTransaction( WindbondCommandSet::UniqueIdLength );

    receiveDataTranscation.afterTransaction =
            [this]
            {
                const auto& dmaReceiveBuffer = m_pBusPtr->getDmaBufferReceive();

                for( std::size_t i{}; i< WindbondCommandSet::UniqueIdLength; ++i )
                {
                    m_spiFlashId[i] = dmaReceiveBuffer[i];
                }
                onRequestDeviceIdCompleted.emit();
            };

    m_pBusPtr->addTransaction( std::move( receiveDataTranscation ) );
    m_pBusPtr->runQueue();
}

void
WinbondFlash::requestJEDEDCId()
{
    Interface::Spi::Transaction requestIdCommandTransaction = writeTransaction(
            WindbondCommandSet::ReadJedecId
    );
    m_pBusPtr->addTransaction( std::move( requestIdCommandTransaction ) );

    Interface::Spi::Transaction receiveDataTranscation =
        readTransaction( WindbondCommandSet::JedecIdLength );
    receiveDataTranscation.afterTransaction =
            [this]
            {
                std::uint32_t JedecDeviceId{};
                const auto dmaReceiveBuffer = m_pBusPtr->getDmaBufferReceive();
                for( std::size_t i{}; i<WindbondCommandSet::JedecIdLength; ++i )
                {
                    JedecDeviceId |= ( dmaReceiveBuffer[i] << ( 16 - i * 8 ) );
                }
                onRequestJedecIdCompleted.emit(JedecDeviceId);
            };
}

void
WinbondFlash::requestEnterSleepMode()
{

}

void
WinbondFlash::requestRestoreFromSleepMode()
{

};

IFlashStorageDriver::TDeviceIdType&
WinbondFlash::getDeviceUniqueId()
{
    return m_spiFlashId;
}

}
