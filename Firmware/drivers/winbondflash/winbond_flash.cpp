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
    ,   const std::uint8_t _blockSize
)
{
    Interface::Spi::Transaction requestWriteEnable = writeTransaction(
        WindbondCommandSet::WriteEnable
    );
    m_pBusPtr->addTransaction( std::move( requestWriteEnable ) );


    Interface::Spi::TransactionDescriptor blockSetup{
            [this,_address,_blockData,_blockSize]
            {
                auto& spiTrasnsmitBuffer = m_pBusPtr->getDmaBufferTransmit();
                spiTrasnsmitBuffer[0] = WindbondCommandSet::PageProgram;
                spiTrasnsmitBuffer[1] = ( _address >> 16 );
                spiTrasnsmitBuffer[2] = ( _address >> 8 );
                spiTrasnsmitBuffer[3] = ( _address >> 0 );

                memcpy(
                        reinterpret_cast<void*>( spiTrasnsmitBuffer.data() + 4 )
                    ,   _blockData
                    ,   _blockSize
                );
            }
        ,   [this]{ onBlockWriteRequestCompleted.emit(); }
        ,   Interface::Spi::TransactionDescriptor::DataSequence{
                reinterpret_cast<const std::uint8_t*>( &m_pBusPtr->getDmaBufferTransmit() )
                ,   _blockSize
            }
        };

    m_pBusPtr->addXferTransaction( std::move( blockSetup ) );
    m_pBusPtr->runQueue();
}

void
WinbondFlash::requestReadBlock(
        const std::uint32_t _address
    ,   const std::uint8_t _blockSize
)
{
    Interface::Spi::Transaction requestRead = writeTransaction(
            WindbondCommandSet::ReadData
        ,   ( _address >> 16 )
        ,   ( _address >> 8 )
        ,   ( _address >> 0 )
    );
    m_pBusPtr->addTransaction( std::move( requestRead ) );

    Interface::Spi::Transaction receiveData =
        readTransaction( _blockSize );

    receiveData.afterTransaction =
            [this]
            {
                onBlockReadRequestCompleted.emit();
            };

    m_pBusPtr->addTransaction( std::move( receiveData ) );
    m_pBusPtr->runQueue();
}

void
WinbondFlash::requestFastReadBlock(
        const std::uint32_t _address
    ,   const std::uint8_t _blockSize
)
{
    Interface::Spi::Transaction requestRead = writeTransaction(
            WindbondCommandSet::ReadData
        ,   ( _address >> 16 )
        ,   ( _address >> 8 )
        ,   ( _address >> 0 )
        ,   0xFF
    );
    m_pBusPtr->addTransaction( std::move( requestRead ) );

    Interface::Spi::Transaction receiveData =
        readTransaction( _blockSize );

    receiveData.afterTransaction =
            [this]
            {
                onBlockReadRequestCompleted.emit();
            };

    m_pBusPtr->addTransaction( std::move( receiveData ) );
    m_pBusPtr->runQueue();
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
    Interface::Spi::Transaction requestId = writeTransaction(
            WindbondCommandSet::ReadUniqueId
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte

        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
    );

    requestId.afterTransaction =
            [this]
            {
                const auto& dmaReceiveBuffer = m_pBusPtr->getDmaBufferReceive();

                for( std::size_t i{}; i< WindbondCommandSet::UniqueIdLength; ++i )
                {
                    m_spiFlashId[i] = dmaReceiveBuffer[i];
                }
                onRequestDeviceIdCompleted.emit();
            };
            
    m_pBusPtr->addTransaction( std::move( requestId ) );
    m_pBusPtr->runQueue();
}

void
WinbondFlash::requestJEDEDCId()
{
    Interface::Spi::Transaction requestIdCommandTransaction = writeTransaction(
            WindbondCommandSet::ReadJedecId
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
        ,   WindbondCommandSet::DummyByte
    );
    requestIdCommandTransaction.afterTransaction =
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
    m_pBusPtr->addTransaction( std::move( requestIdCommandTransaction ) );
    m_pBusPtr->runQueue();
}

void
WinbondFlash::requestEnterSleepMode()
{
    Interface::Spi::Transaction requestPowerdown = writeTransaction(
            WindbondCommandSet::PowerDownMode
    );
    m_pBusPtr->addTransaction( std::move( requestPowerdown ) );
    m_pBusPtr->runQueue();
}

void
WinbondFlash::requestRestoreFromSleepMode()
{
    Interface::Spi::Transaction requestRestoreFromSleep
            = writeTransaction(
                WindbondCommandSet::ResumePowerDownMode
            );
    m_pBusPtr->addTransaction( std::move( requestRestoreFromSleep ) );
    m_pBusPtr->runQueue();
};

IFlashStorageDriver::TDeviceIdType&
WinbondFlash::getDeviceUniqueId()
{
    return m_spiFlashId;
}

}
