#pragma once
#include <gtest/gtest.h>

#include <spi/spi_wrappper_async_templated.hpp>
#include <backends/spi_backend_desktop.hpp>

#include "spi_fake_backend.hpp"

#include <vector>

using TTestParameter = std::vector<std::byte>;

class SpiDriverTest
	: public ::testing::Test
    , public ::testing::WithParamInterface<TTestParameter>
{

protected:

	using TTestDriver = Interface::SpiTemplated::SpiBus<Testing::Spi::SpiBusBackendStub>;

	void SetUp()override
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
        void await_suspend(std::coroutine_handle<> thisCoroutine) const
        {
            pThis->testSpiDriver.transmitBuffer(
                pTransmitBuffer
                , bufferSize
                , thisCoroutine.address()
                , restoreInSpiCtx
            );
        }
    };


    auto sendChunk(
        const std::uint8_t* _pBuffer
        , std::size_t _bufferSize
    )noexcept
    {
        return StubAwaiter
        {
                .restoreInSpiCtx = true
            ,   .pTransmitBuffer = _pBuffer
            ,   .pThis = this
            ,   .bufferSize = static_cast<std::uint16_t>(_bufferSize)
        };
    }

    std::vector<std::byte> TransactionsToDataStream()
    {
        return testSpiDriver.getBackendImpl().getTransmittedData();
    }

protected:
	TTestDriver testSpiDriver;
};