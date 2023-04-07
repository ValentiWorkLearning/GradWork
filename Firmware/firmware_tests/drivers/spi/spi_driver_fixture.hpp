#pragma once
#include <gtest/gtest.h>

#include <backends/spi_backend_desktop.hpp>
#include <spi/spi_wrapper_async_templated.hpp>

#include "spi_fake_backend.hpp"

#include <string>
#include <tuple>
#include <vector>

class SpiDriverTest
    : public ::testing::Test
    , public ::testing::WithParamInterface<std::tuple<std::uint16_t, std::string_view>>
{

public:
    using TTestDriver = Interface::SpiTemplated::SpiBus<Testing::Spi::SpiBusBackendStub>;

protected:
    void SetUp() override
    {
    }

    struct StubAwaiter
    {
        bool restoreInSpiCtx = false;
        const std::uint8_t* pTransmitBuffer;
        SpiDriverTest* pThis;
        std::uint16_t bufferSize;

        bool await_ready() const noexcept
        {
            const bool isAwaitReady = pTransmitBuffer == nullptr || bufferSize == 0;
            return isAwaitReady;
        }
        void await_resume() const noexcept
        {
        }
        void await_suspend(stdcoro::coroutine_handle<> thisCoroutine) const
        {
            pThis->testSpiDriver.transmitBuffer(
                std::span(pTransmitBuffer, bufferSize), thisCoroutine.address(), restoreInSpiCtx);
        }
    };

    struct StubXferAwaiter
    {
        bool restoreInSpiCtx = false;
        std::span<const std::uint8_t> pTransmitBuffer;
        std::span<std::uint8_t> pReceiveBuffer;
        SpiDriverTest* pThis;

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
            pThis->testSpiDriver.xferBuffer(
                pTransmitBuffer, pReceiveBuffer, thisCoroutine.address(), restoreInSpiCtx);
        }
    };

    auto sendChunk(const std::uint8_t* _pBuffer, std::size_t _bufferSize) noexcept
    {
        return StubAwaiter{
            .restoreInSpiCtx = true,
            .pTransmitBuffer = _pBuffer,
            .pThis = this,
            .bufferSize = static_cast<std::uint16_t>(_bufferSize)};
    }

    auto xferChunk(
        std::span<const std::uint8_t> _pTrasnmitBuffer,
        std::span<std::uint8_t> _pReceiveBuffer) noexcept
    {
        return StubXferAwaiter{
            .restoreInSpiCtx = true,
            .pTransmitBuffer = _pTrasnmitBuffer,
            .pReceiveBuffer = _pReceiveBuffer,
            .pThis = this};
    }

    CoroUtils::Task<std::span<std::uint8_t>> xferTransaction(
        std::span<const std::uint8_t> _pTransmitCommand,
        std::span<std::uint8_t> _pReceiveBuffer) noexcept
    {
        co_await xferChunk(_pTransmitCommand, _pReceiveBuffer);
        co_return _pReceiveBuffer;
    }

    using TDataStream = std::vector<std::byte>;
    TDataStream TransactionsToDataStream()
    {
        return testSpiDriver.getBackendImpl().getTransmittedData();
    }

protected:
    TTestDriver testSpiDriver;
};