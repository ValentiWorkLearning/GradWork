#pragma once

#include "winbond_commandset.hpp"

#include <span>
#include <utils/CoroUtils.hpp>

namespace ExternalFlash
{

template <typename TSpiBusInstance> class WinbondFlashDriver
{
    using This_t = WinbondFlashDriver<TSpiBusInstance>;

public:
    void requestWriteBlock(
        const std::uint32_t _address,
        const std::uint8_t* _blockData,
        const std::uint8_t _blockSize) noexcept
    {
    }

    void requestReadBlock(const std::uint32_t _address, const std::uint8_t _blockSize) noexcept
    {
    }
    void requestFastReadBlock(const std::uint32_t _address, const std::uint8_t _blockSize) noexcept
    {
    }

    void requestChipErase() noexcept
    {
    }

    CoroUtils::Task<std::span<std::uint8_t>> requestDeviceId() noexcept
    {
        auto receivedData = co_await prepareXferTransaction(
            WindbondCommandSet::ReadUniqueId,

            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,
            WindbondCommandSet::DummyByte,

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
            WindbondCommandSet::ReadJedecId,
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

    void requestEnterSleepMode() noexcept
    {
    }

    void requestRestoreFromSleepMode() noexcept
    {
    }

private:
    template <typename... Args> auto prepareXferTransaction(Args&&... argList)
    {
        auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
        auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();
        processTransmitBuffer(transmitBuffer, std::forward_as_tuple(argList...));

        constexpr std::size_t TransmitSize = sizeof...(argList);
        constexpr std::size_t ReceiveSize = TransmitSize;

        return xferTransaction(
            std::span(transmitBuffer.data(), TransmitSize),
            std::span(receiveBuffer.data(), TransmitSize));
    }

    CoroUtils::Task<std::span<std::uint8_t>> xferTransaction(
        std::span<const std::uint8_t> _pTransmitCommand,
        std::span<std::uint8_t> _pReceiveBuffer) noexcept
    {
        co_await xferChunk(_pTransmitCommand, _pReceiveBuffer);
        co_return std::span(_pReceiveBuffer.data() + 1, _pReceiveBuffer.size() - 1);
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
        void await_suspend(std::coroutine_handle<> thisCoroutine) const
        {
            pThis->getSpiBus()->xferBuffer(
                pTransmitBuffer, pReceiveBuffer, thisCoroutine.address(), restoreInSpiCtx);
        }
    };

    auto getSpiBus() noexcept
    {
        return &m_spiBus;
    }

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

private:
    TSpiBusInstance m_spiBus;
};

}; // namespace ExternalFlash