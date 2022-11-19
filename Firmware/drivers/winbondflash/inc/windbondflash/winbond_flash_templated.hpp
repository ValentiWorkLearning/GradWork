#pragma once

#include "winbond_commandset.hpp"

#include <span>
#include <utils/CoroUtils.hpp>

#include <cassert>
#include <tuple>
#include <utility>

namespace ExternalFlash
{

template <typename TSpiBusInstance> class WinbondFlashDriver
{
    using This_t = WinbondFlashDriver<TSpiBusInstance>;

public:
    CoroUtils::VoidTask pageWrite(
        const std::uint32_t _address,
        std::span<const std::uint8_t> _blockData) noexcept
    {
        constexpr std::uint16_t PageSize = 256;

        assert(_blockData.size() < PageSize);

        using TTupleProgram = decltype(std::forward_as_tuple(
            WindbondCommandSet::PageProgram,
            static_cast<std::uint8_t>(_address & 0x00'FF'00'00 >> 16),
            static_cast<std::uint8_t>(_address & 0x00'00'FF'00 >> 8),
            static_cast<std::uint8_t>(_address & 0x00'00'00'FF)));
        constexpr bool ManageSpiTransactions = false;

        getSpiBus()->setCsPinLow();

        using TTupleWe = decltype(std::forward_as_tuple(WindbondCommandSet::WriteEnable));
        co_await prepareXferTransaction<TTupleWe, ManageSpiTransactions>(
            std::forward_as_tuple(WindbondCommandSet::WriteEnable));

        co_await prepareXferTransaction<TTupleProgram, ManageSpiTransactions>(std::forward_as_tuple(
            WindbondCommandSet::PageProgram,
            static_cast<std::uint8_t>(_address & 0x00'FF'00'00 >> 16),
            static_cast<std::uint8_t>(_address & 0x00'00'FF'00 >> 8),
            static_cast<std::uint8_t>(_address & 0x00'00'00'FF)));

        co_await transmitChunk(std::span(_blockData.data(), _blockData.size()));

        getSpiBus()->setCsPinHigh();
    }

    CoroUtils::Task<std::span<std::uint8_t>> requestReadBlock(
        const std::uint32_t _address,
        const std::uint16_t _blockSize) noexcept
    {
        constexpr std::uint16_t PageSize = 256;

        assert(_blockSize < PageSize);

        using TTupleRead = decltype(std::forward_as_tuple(
            WindbondCommandSet::ReadData,
            static_cast<std::uint8_t>(_address & 0x00'FF'00'00 >> 16),
            static_cast<std::uint8_t>(_address & 0x00'00'FF'00 >> 8),
            static_cast<std::uint8_t>(_address & 0x00'00'00'FF)));
        constexpr bool ManageSpiTransactions = false;

        getSpiBus()->setCsPinLow();

        co_await prepareXferTransaction<TTupleRead, ManageSpiTransactions>(std::forward_as_tuple(
            WindbondCommandSet::ReadData,
            static_cast<std::uint8_t>((_address & 0x00'FF'00'00) >> 16),
            static_cast<std::uint8_t>((_address & 0x00'00'FF'00) >> 8),
            static_cast<std::uint8_t>(_address & 0x00'00'00'FF)));

        auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
        auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();

        std::fill_n(
            transmitBuffer.begin(),
            _blockSize,
            WindbondCommandSet::DummyByte);

        auto receivedData = co_await xferTransaction(
            std::span(transmitBuffer.data(), _blockSize),
            std::span(receiveBuffer.data(), _blockSize));

        getSpiBus()->setCsPinHigh();

        co_return receivedData;
    }
    void requestFastReadBlock(const std::uint32_t _address, const std::uint8_t _blockSize) noexcept
    {
    }

    CoroUtils::VoidTask requestChipErase() noexcept
    {
        co_await prepareXferTransaction(std::forward_as_tuple(WindbondCommandSet::ChipErase));
    }

    CoroUtils::VoidTask requestPowerDown() noexcept
    {
        co_await prepareXferTransaction(std::forward_as_tuple(WindbondCommandSet::PowerDownMode));
    }

    CoroUtils::VoidTask resumePowerDown() noexcept
    {
        co_await prepareXferTransaction(
            std::forward_as_tuple(WindbondCommandSet::ResumePowerDownMode));
    }

    CoroUtils::Task<std::span<std::uint8_t>> requestDeviceId() noexcept
    {
        auto receivedData = co_await prepareXferTransaction(
            std::forward_as_tuple(
                WindbondCommandSet::ReadUniqueId,
                WindbondCommandSet::DummyByte,
                WindbondCommandSet::DummyByte,
                WindbondCommandSet::DummyByte,
                WindbondCommandSet::DummyByte),

            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte);
        co_return std::span(receivedData.data(), receivedData.size());
    }

    CoroUtils::Task<std::uint32_t> requestJEDEDCId() noexcept
    {
        auto receivedData = co_await prepareXferTransaction(
            std::forward_as_tuple(WindbondCommandSet::ReadJedecId),
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte);

        std::uint32_t JedecDeviceId{};
        for (std::size_t i{}; i < WindbondCommandSet::JedecIdLength; ++i)
        {
            JedecDeviceId |= (receivedData[i] << (16 - i * 8));
        }

        co_return JedecDeviceId;
    }

    const auto getSpiBus() const noexcept
    {
        return &m_spiBus;
    }

    auto getSpiBus() noexcept
    {
        return &m_spiBus;
    }

private:
    template <typename TCommand, bool manageCsPin = true, typename... Args>
    CoroUtils::Task<std::span<std::uint8_t>> prepareXferTransaction(
        TCommand&& _command,
        Args&&... _argList)
    {
        auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
        auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();

        if constexpr (manageCsPin)
            getSpiBus()->setCsPinLow();

        processTransmitBuffer(transmitBuffer, std::forward<TCommand>(_command));

        constexpr std::size_t CommandSize = std::tuple_size_v<TCommand>;
        const auto spanToSend = std::span(transmitBuffer.data(), CommandSize);
        co_await transmitChunk(spanToSend);

        constexpr std::size_t DummyListSize = sizeof...(_argList);

        processTransmitBuffer(transmitBuffer, std::forward_as_tuple(_argList...));

        auto receivedBlockSpan = co_await xferTransaction(
            std::span(transmitBuffer.data(), DummyListSize),
            std::span(receiveBuffer.data(), DummyListSize));

        if constexpr (manageCsPin)
            getSpiBus()->setCsPinHigh();

        co_return std::span(receiveBuffer.data(), DummyListSize);
    }

    template <typename TTuple, bool manageCsPin = true>
    CoroUtils::VoidTask prepareXferTransaction(TTuple&& _command)
    {
        auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
        auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();

        if constexpr (manageCsPin)
            getSpiBus()->setCsPinLow();

        processTransmitBuffer(transmitBuffer, std::forward<TTuple>(_command));

        constexpr std::size_t CommandSize = std::tuple_size_v<TTuple>;

        co_await transmitChunk(std::span(transmitBuffer.data(), CommandSize));

        if constexpr (manageCsPin)
            getSpiBus()->setCsPinHigh();
    }

    CoroUtils::Task<std::span<std::uint8_t>> xferTransaction(
        std::span<const std::uint8_t> _pTransmitCommand,
        std::span<std::uint8_t> _pReceiveBuffer) noexcept
    {
        co_await xferChunk(_pTransmitCommand, _pReceiveBuffer);
        co_return std::span(_pReceiveBuffer.data(), _pReceiveBuffer.size());
    }

    template <
        typename TTRansmitBuffer,
        typename TArgsTuple,
        typename Indexes = std::make_index_sequence<std::tuple_size_v<TArgsTuple>>>
    void processTransmitBuffer(TTRansmitBuffer&& _transmitBuffer, TArgsTuple&& _argsTuple)
    {
        processTransmitBufferImpl(
            std::forward<TTRansmitBuffer&&>(_transmitBuffer),
            std::forward<TArgsTuple&&>(_argsTuple),
            Indexes{});
    }

    template <typename TTRansmitBuffer, typename TArgsTuple, std::size_t... Index>
    void processTransmitBufferImpl(
        TTRansmitBuffer&& _transmitBuffer,
        TArgsTuple&& _argsTuple,
        std::index_sequence<Index...>)
    {
        ((_transmitBuffer[Index] = std::get<Index>(_argsTuple)), ...);
    }

private:
    struct XferAwaiter
    {
        bool restoreInSpiCtx = false;
        std::span<const std::uint8_t> pTransmitBuffer;
        std::span<std::uint8_t> pReceiveBuffer;
        This_t* pThis;

        bool await_ready() const noexcept
        {
            const bool isAwaitReady = pTransmitBuffer.size() == 0;
            return isAwaitReady;
        }
        void await_resume() const noexcept
        {
        }
        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const
        {
            pThis->getSpiBus()->xferBuffer(
                pTransmitBuffer, pReceiveBuffer, thisCoroutine.address(), restoreInSpiCtx);
        }
    };

    struct TransmitAwaiter
    {
        bool restoreInSpiCtx = false;
        std::span<const std::uint8_t> pTransmitBuffer;
        This_t* pThis;

        bool await_ready() const noexcept
        {
            const bool isAwaitReady = pTransmitBuffer.size() == 0;
            return isAwaitReady;
        }
        void await_resume() const noexcept
        {
        }
        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const
        {
            pThis->getSpiBus()->transmitBuffer(
                pTransmitBuffer,
                thisCoroutine.address(),
                restoreInSpiCtx);
        }
    };

    auto xferChunk(
        std::span<const std::uint8_t> _pTrasnmitBuffer,
        std::span<std::uint8_t> _pReceiveBuffer) noexcept
    {
        return XferAwaiter{
            .restoreInSpiCtx = true,
            .pTransmitBuffer = _pTrasnmitBuffer,
            .pReceiveBuffer = _pReceiveBuffer,
            .pThis = this};
    }

    auto transmitChunk(std::span<const std::uint8_t> _pTrasnmitBuffer) noexcept
    {
        return TransmitAwaiter{
            .restoreInSpiCtx = true, .pTransmitBuffer = _pTrasnmitBuffer, .pThis = this};
    }

private:
    TSpiBusInstance m_spiBus;
};

}; // namespace ExternalFlash