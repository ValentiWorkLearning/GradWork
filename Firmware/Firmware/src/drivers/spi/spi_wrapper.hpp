#pragma once

#include "nrfx_spim.h"
#include "pca10040.h"

#include "SimpleSignal.hpp"

#include "transaction_item.hpp"

#include <queue>
#include <memory>
#include <atomic>

#include <etl/vector.h>
#include <etl/queue.h>

namespace Interface::Spi
{

namespace SpiInstance
{
    struct M1
    {
        static constexpr std::uint8_t ClockPin = SPIM1_SCK_PIN;
        static constexpr std::uint8_t MisoPin = SPIM1_MISO_PIN;
        static constexpr std::uint8_t MosiPin = SPIM1_MOSI_PIN;
        static constexpr std::uint8_t SlaveSelectPin = SPIM1_SS_PIN;

        static constexpr std::uint32_t Register = NRF_SPIM1_BASE;
        static constexpr uint8_t DriverInstance = NRFX_SPIM1_INST_IDX;
    };

    struct M2
    {
        static constexpr std::uint8_t ClockPin = SPIM2_SCK_PIN;
        static constexpr std::uint8_t MisoPin = SPIM2_MISO_PIN;
        static constexpr std::uint8_t MosiPin = SPIM2_MOSI_PIN;
        static constexpr std::uint8_t SlaveSelectPin = SPIM2_SS_PIN;

        static constexpr std::uint32_t Register = NRF_SPIM2_BASE;
        static constexpr uint8_t DriverInstance = NRFX_SPIM2_INST_IDX;
    };
};

class SpiBus
{

public:

    explicit SpiBus(
            std::uint8_t _clockPin
        ,   std::uint8_t _misoPin
        ,   std::uint8_t _mosiPin
        ,   std::uint8_t _chipSelectPin
        ,   std::uint32_t _pRegister
        ,   std::uint8_t _driverInstance
    );

    ~SpiBus() = default;

public:

    static constexpr std::uint16_t DmaBufferSize = 255;
    using DmaBufferType = etl::vector<std::uint8_t,DmaBufferSize>;

    std::uint16_t getDmaBufferSize();

public:

    void sendData( std::uint8_t _data );

    void sendChunk( const std::uint8_t* _pBuffer, const size_t _bufferSize );

    void receiveChunk( std::uint8_t* _pBuffer, const size_t _bufferSize );

    DmaBufferType& getDmaBuffer();

    Simple::Signal<void()> onTransactionCompleted;

public:

    void addTransaction( Transaction&& _item );

    void runQueue();

    size_t getQueueSize() const;

private:

    void spimEventHandler(
            nrfx_spim_evt_t const* _pEvent
        ,   void* _pContext
    );

    void performTransaction( uint16_t _dataSize );

private:

    std::atomic<bool> m_isTransactionCompleted;
    nrfx_spim_t m_spiHandle;

    static constexpr inline int QueueSize = 32;

    using TTransactionStorage = etl::queue<
            Transaction
        ,   QueueSize
        ,   etl::memory_model::MEMORY_MODEL_SMALL
    >;

    DmaBufferType DmaArray;
    TTransactionStorage m_transactionsQueue;
};

template< typename TSpiInstance >
std::unique_ptr<SpiBus> createSpiBus()
{
    return std::make_unique<SpiBus>(
            TSpiInstance::ClockPin
        ,   TSpiInstance::MisoPin
        ,   TSpiInstance::MosiPin
        ,   TSpiInstance::SlaveSelectPin
        ,   TSpiInstance::Register
        ,   TSpiInstance::DriverInstance
    );
}

} // namespace Interface
