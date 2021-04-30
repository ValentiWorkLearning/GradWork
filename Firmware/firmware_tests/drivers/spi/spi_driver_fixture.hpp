#pragma once
#include <gtest/gtest.h>

#include <spi/spi_wrappper_async_templated.hpp>
#include <backends/spi_backend_desktop.hpp>

#include "spi_fake_backend.hpp"

class SpiDriverTest
	: public ::testing::Test
{

protected:

	using TTestDriver = Interface::SpiTemplated::SpiBus<Testing::Spi::SpiBusBackendStub>;

	void SetUp()override
	{
	}


private:
	TTestDriver testSpiDriver;
};