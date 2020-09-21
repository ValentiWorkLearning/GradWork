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
    struct M1;
    struct M2;
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

    ~SpiBus();

public:

    static constexpr std::uint16_t DmaBufferSize = 255;
    using DmaBufferType = etl::vector<std::uint8_t,DmaBufferSize>;

    std::uint16_t getDmaBufferSize() noexcept;

public:

    void addXferTransaction( TransactionDescriptor&& _deskcriptor ) noexcept;

    void sendData( std::uint8_t _data )noexcept;

    void sendChunk( const std::uint8_t* _pBuffer, const size_t _bufferSize )noexcept;

    void xferChunk(
            const std::uint8_t* _pTransmitBuffer
        ,   const size_t _transmitBufferSize
    )noexcept;

    void receiveAsync( const size_t bytesCount )noexcept;

    DmaBufferType& getDmaBufferTransmit()noexcept;
    DmaBufferType& getDmaBufferReceive()noexcept;

    Simple::Signal<void()> onTransactionCompleted;

public:

    void addTransaction( Transaction&& _item )noexcept;

    void runQueue()noexcept;

    size_t getQueueSize() const noexcept;

    enum class TCompletedEvent
    {
            TransactionCompleted
        ,   TranscationFailed
        ,   Unknown
    };

    void handleEvent( TCompletedEvent _eventToHandle )noexcept;

private:

    void performTransaction( uint16_t _dataSize )noexcept;

    void setupBlockTransactionInternal(
            std::function<void()> beforeTransaction
        ,   std::function<void()> afterTransaction
        ,   const TransactionDescriptor::DataSequence& dataSequence
    )noexcept;

    std::uint32_t getTransitionOffset()noexcept;

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

template< typename TSpiInstance >
std::unique_ptr<SpiBus> createSpiBus();

} // namespace Interface
