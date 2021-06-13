#pragma once
#include <gtest/gtest.h>

#include <backends/spi_backend_desktop.hpp>
#include <spi/spi_wrapper_async_templated.hpp>

#include <windbondflash/winbond_flash_templated.hpp>

#include <string>
#include <tuple>
#include <vector>

// TODO Fix include more clearly
#include "../spi/spi_fake_backend.hpp"

class FlashDriverTest : public ::testing::Test
{

public:
    using TFlashTestDriver = ExternalFlash::WinbondFlashDriver<
        Interface::SpiTemplated::SpiBus<Testing::Spi::SpiBusBackendStub>>;
    using TDataStream = std::vector<std::byte>;

protected:
    void SetUp() override
    {
    }

    void setReceivedSpiStream(const TDataStream& _steram)
    {
        flashDriver.getSpiBus()->getBackendImpl().setReceivedStream(_steram);
    }

protected:
    TFlashTestDriver flashDriver;
};
