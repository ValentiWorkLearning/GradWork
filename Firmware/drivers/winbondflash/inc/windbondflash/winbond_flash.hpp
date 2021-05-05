#pragma once


#include <memory>
#include <cstdint>

#include "ih/drivers/ih_iexternal_flash.hpp"

#include "spi/spi_wrapper.hpp"

#include "utils/SimpleSignal.hpp"
#include "winbond_commandset.hpp"

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
        std::unique_ptr<Interface::Spi::SpiBus>&& _busPtr
    );

    ~WinbondFlash()noexcept override = default;

public:

    void requestWriteBlock(
            const std::uint32_t _address
        ,   const std::uint8_t* _blockData
        ,   const std::uint8_t _blockSize
    )noexcept override;

    void requestReadBlock(
            const std::uint32_t _address
        ,   const std::uint8_t _blockSize
    )noexcept override;

    void requestFastReadBlock(
            const std::uint32_t _address
        ,   const std::uint8_t _blockSize
    )noexcept override;

    void requestChipErase()noexcept override;

    void requestDeviceId()noexcept override;

    void requestJEDEDCId()noexcept override;

    void requestEnterSleepMode()noexcept override;

    void requestRestoreFromSleepMode()noexcept override;

    IFlashStorageDriver::TDeviceIdType&
    getDeviceUniqueId()noexcept override;

private:

    template< typename ... Args >
    auto writeTransaction(
            Args... _chunkArgs
    )noexcept
    {
        std::array chunk = { static_cast<std::uint8_t>(_chunkArgs)... };
        Interface::Spi::Transaction chunkTransaction{};

        chunkTransaction.transactionAction =
            [ this, chunkToSend = std::move( chunk ) ]
            {
                m_pBusPtr->xferChunk(
                        reinterpret_cast<const std::uint8_t*>( chunkToSend.data() )
                    ,   chunkToSend.size()
                );
            };

        return chunkTransaction;
    }

    auto readTransaction( const size_t _bytesCount )noexcept
    {
        Interface::Spi::Transaction receiveTransaction{};
        receiveTransaction.transactionAction =
            [this,_bytesCount]
            {
                m_pBusPtr->receiveAsync( _bytesCount );
            };

        return receiveTransaction;
    }
private:
    std::unique_ptr<Interface::Spi::SpiBus> m_pBusPtr;

    std::array<std::uint8_t,WindbondCommandSet::UniqueIdLength> m_spiFlashId;

};

}
