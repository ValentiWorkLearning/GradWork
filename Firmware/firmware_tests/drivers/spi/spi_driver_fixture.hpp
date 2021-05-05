#pragma once
#include <gtest/gtest.h>

#include <spi/spi_wrapper_async_templated.hpp>
#include <backends/spi_backend_desktop.hpp>

#include "spi_fake_backend.hpp"

#include <vector>
#include <string>
#include <tuple>

class SpiDriverTest
	: public ::testing::Test
    , public ::testing::WithParamInterface<std::tuple<std::uint16_t,std::string_view>>
{


public:

	using TTestDriver = Interface::SpiTemplated::SpiBus<Testing::Spi::SpiBusBackendStub>;

protected:

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

    using TDataStream = std::vector<std::byte>;
    TDataStream TransactionsToDataStream()
    {
        return testSpiDriver.getBackendImpl().getTransmittedData();
    }

protected:
	TTestDriver testSpiDriver;
};