#pragma once

#include "winbond_commandset.hpp"

#include <span>
#include <utils/CoroUtils.hpp>
#include <utils/coroutine/SyncWait.hpp>

#include <cassert>
#include <logger/logger_service.hpp>
#include <tuple>
#include <utility>

namespace ExternalFlash
{

template <typename TSpiBusInstance> class WinbondFlashDriver
{
    using This_t = WinbondFlashDriver<TSpiBusInstance>;

    struct ChipSelectGuard
    {
        ChipSelectGuard(This_t* pThis) : m_pThis{pThis}
        {
            m_pThis->getSpiBus()->setCsPinLow();
        }

        ~ChipSelectGuard()
        {
            m_pThis->getSpiBus()->setCsPinHigh();
        }

        This_t* m_pThis;
    };

public:
    CoroUtils::VoidTask pageWrite(
        const std::uint32_t _address,
        std::span<const std::uint8_t> _blockData) noexcept
    {

        LOG_TRACE("WinbondFlashDriver pageWrite");
        constexpr std::uint16_t PageSize = 256;

        assert(_blockData.size() <= PageSize);

        co_await eraseSector(_address);

        LOG_TRACE("WinbondFlashDriver XFER WE");

        {
            ChipSelectGuard csGuard{this};
            co_await prepareXferTransaction(std::forward_as_tuple(WindbondCommandSet::WriteEnable));
        }
        while (co_await checkIsBusy())
        {
            LOG_TRACE("WinbondFlashDriver wait for write completion");
            co_yield CoroUtils::CoroQueueMainLoop::GetInstance();
        }

        {
            ChipSelectGuard csGuard{this};

            LOG_TRACE("WinbondFlashDriver XFER PageProgram");
            co_await prepareXferTransaction(std::forward_as_tuple(
                WindbondCommandSet::PageProgram,
                static_cast<std::uint8_t>((_address & 0x00'FF'00'00) >> 16),
                static_cast<std::uint8_t>((_address & 0x00'00'FF'00) >> 8),
                static_cast<std::uint8_t>(_address & 0x00'00'00'FF)));

            LOG_TRACE("WinbondFlashDriver XFER blockData");
            co_await transmitChunk(std::span(_blockData.data(), _blockData.size()));
        }

        while (co_await checkIsBusy())
        {
            LOG_TRACE("WinbondFlashDriver wait for write completion");
            co_yield CoroUtils::CoroQueueMainLoop::GetInstance();
        }

        LOG_TRACE("WinbondFlashDriver XFER completed write");
    }

    CoroUtils::Task<std::span<std::uint8_t>> requestReadBlock(
        const std::uint32_t _address,
        const std::uint16_t _blockSize) noexcept
    {
        constexpr std::uint16_t PageSize = 256;

        LOG_TRACE(fmt::format("WinbondFlashDriver requestReadBlock: {},{}", _blockSize, PageSize));
        assert(_blockSize <= PageSize);
        std::span<std::uint8_t> receivedData{};

        {
            ChipSelectGuard csGuard{this};

            LOG_TRACE("WinbondFlashDriver prepareXferTransaction BEGIN");
            co_await prepareXferTransaction(std::forward_as_tuple(
                WindbondCommandSet::ReadData,
                static_cast<std::uint8_t>((_address & 0x00'FF'00'00) >> 16),
                static_cast<std::uint8_t>((_address & 0x00'00'FF'00) >> 8),
                static_cast<std::uint8_t>(_address & 0x00'00'00'FF)));

            LOG_TRACE("WinbondFlashDriver prepareXferTransaction COMPLETION");
            auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
            auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();

            std::fill_n(transmitBuffer.begin(), _blockSize, WindbondCommandSet::DummyByte);

            receivedData = co_await xferTransaction(
                std::span(transmitBuffer.data(), _blockSize),
                std::span(receiveBuffer.data(), _blockSize));

            LOG_TRACE("WinbondFlashDriver xferTransaction receive");
        }
        while (co_await checkIsBusy())
        {
            LOG_TRACE("WinbondFlashDriver READ wait for read completion");
            co_yield CoroUtils::CoroQueueMainLoop::GetInstance();
        }
        LOG_TRACE("WinbondFlashDriver return back");
        co_return receivedData;
    }
    void requestFastReadBlock(const std::uint32_t _address, const std::uint8_t _blockSize) noexcept
    {
    }

    CoroUtils::VoidTask requestChipErase() noexcept
    {
        ChipSelectGuard csGuard{this};
        co_await prepareXferTransaction(std::forward_as_tuple(WindbondCommandSet::ChipErase));
    }

    CoroUtils::VoidTask requestPowerDown() noexcept
    {
        ChipSelectGuard csGuard{this};
        co_await prepareXferTransaction(std::forward_as_tuple(WindbondCommandSet::PowerDownMode));
    }

    CoroUtils::VoidTask resumePowerDown() noexcept
    {
        ChipSelectGuard csGuard{this};
        co_await prepareXferTransaction(
            std::forward_as_tuple(WindbondCommandSet::ResumePowerDownMode));
    }

    CoroUtils::Task<std::span<std::uint8_t>> requestDeviceId() noexcept
    {
        ChipSelectGuard csGuard{this};
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
        ChipSelectGuard csGuard{this};
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

    CoroUtils::Task<bool> checkIsBusy() noexcept
    {
        ChipSelectGuard csGuard{this};

        LOG_TRACE("WinbondFlashDriver checkIsBusy");

        auto busyStatusRegister = co_await prepareXferTransaction(
            std::forward_as_tuple(WindbondCommandSet::ReadStatusRegister1),
            WindbondCommandSet::DummyByte);

        LOG_TRACE("WinbondFlashDriver checkIsBusy completion");
        co_return busyStatusRegister[0] & WindbondCommandSet::Masks::EraseWriteInProgress;
    }

    const auto getSpiBus() const noexcept
    {
        return &m_spiBus;
    }

    auto getSpiBus() noexcept
    {
        return &m_spiBus;
    }

    CoroUtils::VoidTask eraseSector(std::uint32_t _address)
    {
        {
            ChipSelectGuard guard{this};
            co_await prepareXferTransaction(std::forward_as_tuple(
                WindbondCommandSet::SectorErase4KB,
                static_cast<std::uint8_t>((_address & 0x00'FF'00'00) >> 16),
                static_cast<std::uint8_t>((_address & 0x00'00'FF'00) >> 8),
                static_cast<std::uint8_t>(_address & 0x00'00'00'FF)));
        }
        while (co_await checkIsBusy())
        {
            LOG_TRACE("WinbondFlashDriver wait for the eraseSector completion");
            co_yield CoroUtils::CoroQueueMainLoop::GetInstance();
        }
    }

private:
    template <typename TCommand, typename... Args>
    CoroUtils::Task<std::span<std::uint8_t>> prepareXferTransaction(
        TCommand&& _command,
        Args&&... _argList)
    {
        auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
        auto& receiveBuffer = getSpiBus()->getDmaBufferReceive();

        processTransmitBuffer(transmitBuffer, std::forward<TCommand>(_command));

        constexpr std::size_t CommandSize = std::tuple_size_v<TCommand>;
        const auto spanToSend = std::span(transmitBuffer.data(), CommandSize);
        co_await transmitChunk(spanToSend);

        constexpr std::size_t DummyListSize = sizeof...(_argList);

        processTransmitBuffer(transmitBuffer, std::forward_as_tuple(_argList...));

        auto receivedBlockSpan = co_await xferTransaction(
            std::span(transmitBuffer.data(), DummyListSize),
            std::span(receiveBuffer.data(), DummyListSize));

        co_return std::span(receiveBuffer.data(), DummyListSize);
    }

    template <typename TTuple> CoroUtils::VoidTask prepareXferTransaction(TTuple&& _command)
    {
        auto& transmitBuffer = getSpiBus()->getDmaBufferTransmit();
        processTransmitBuffer(transmitBuffer, std::forward<TTuple>(_command));

        constexpr std::size_t CommandSize = std::tuple_size_v<TTuple>;

        co_await transmitChunk(std::span(transmitBuffer.data(), CommandSize));
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
        void await_suspend(std::coroutine_handle<> thisCoroutine) const
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
        void await_suspend(std::coroutine_handle<> thisCoroutine) const
        {
            pThis->getSpiBus()->transmitBuffer(
                pTransmitBuffer, thisCoroutine.address(), restoreInSpiCtx);
        }
    };

    auto xferChunk(
        std::span<const std::uint8_t> _pTrasnmitBuffer,
        std::span<std::uint8_t> _pReceiveBuffer) noexcept
    {
        return XferAwaiter{
            .restoreInSpiCtx = false,
            .pTransmitBuffer = _pTrasnmitBuffer,
            .pReceiveBuffer = _pReceiveBuffer,
            .pThis = this};
    }

    auto transmitChunk(std::span<const std::uint8_t> _pTrasnmitBuffer) noexcept
    {
        return TransmitAwaiter{
            .restoreInSpiCtx = false, .pTransmitBuffer = _pTrasnmitBuffer, .pThis = this};
    }

private:
    TSpiBusInstance m_spiBus;
};

}; // namespace ExternalFlash