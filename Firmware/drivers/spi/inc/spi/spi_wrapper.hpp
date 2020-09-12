#pragma once

#include "ih/drivers/transaction_item.hpp"

#include "utils/SimpleSignal.hpp"

#include <memory>
#include <atomic>

#include <etl/vector.h>
#include <etl/queue.h>

namespace Interface::Spi
{

namespace SpiInstance
{
    struct SpiDecriptor
    {
        std::uint8_t ClockPin;
        std::uint8_t MisoPin;
        std::uint8_t MosiPin;
        std::uint8_t SlaveSelectPin;

        std::uint32_t Register;
        uint8_t DriverInstance;
    };

    enum class TSpiDescriptor
    {
            M1
        ,   M2
    };
    SpiDecriptor fillSpiDescriptor(TSpiDescriptor _descriptor);
};

class SpiBus
{

public:

    explicit SpiBus(const SpiInstance::SpiDecriptor& _spiDescriptor);

    SpiBus (SpiBus&& _other);
    SpiBus& operator= (SpiBus&& x) = default;

    ~SpiBus();

public:

    static constexpr std::uint16_t DmaBufferSize = 255;
    using DmaBufferType = etl::vector<std::uint8_t,DmaBufferSize>;

    std::uint16_t getDmaBufferSize();

public:

    void addXferTransaction( TransactionDescriptor&& _deskcriptor );

    void sendData( std::uint8_t _data );

    void sendChunk( const std::uint8_t* _pBuffer, const size_t _bufferSize );

    void xferChunk(
            const std::uint8_t* _pTransmitBuffer
        ,   const size_t _transmitBufferSize
    );

    void receiveAsync( const size_t bytesCount );

    DmaBufferType& getDmaBufferTransmit();
    DmaBufferType& getDmaBufferReceive();

    Simple::Signal<void()> onTransactionCompleted;

public:

    void addTransaction( Transaction&& _item );

    void runQueue();

    size_t getQueueSize() const;

    enum class TCompletedEvent
    {
            TransactionCompleted
        ,   TranscationFailed
        ,   Unknown
    };

    void handleEvent( TCompletedEvent _eventToHandle );

private:

    void performTransaction( uint16_t _dataSize );

    void setupBlockTransactionInternal(
            std::function<void()> beforeTransaction
        ,   std::function<void()> afterTransaction
        ,   const TransactionDescriptor::DataSequence& dataSequence
    );

    std::uint32_t getTransitionOffset();

private:

    std::atomic<bool> m_isTransactionCompleted;
    std::uint32_t m_completedTransitionsCount;

    static constexpr inline int QueueSize = 60;

    using TTransactionStorage = etl::queue<
            Transaction
        ,   QueueSize
        ,   etl::memory_model::MEMORY_MODEL_SMALL
    >;

    class SpiBackendImpl;
    std::unique_ptr<SpiBackendImpl> m_pSpiBackendImpl;

    DmaBufferType DmaArrayTransmit;
    DmaBufferType DmaArrayReceive;
    TTransactionStorage m_transactionsQueue;
};

} // namespace Interface
