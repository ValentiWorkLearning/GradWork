#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "spi_driver_fixture.hpp"


TEST_F(SpiDriverTest, ExpectAnyTransmissionOccured)
{
	static constexpr std::uint8_t DataBlock = 223;
	static constexpr std::uint8_t DataSize = 1;

	co_await sendChunk(&DataBlock, DataSize);

	constexpr size_t TransactionsCount = 1;
	EXPECT_EQ(testSpiDriver.getBackendImpl().getTransactionsSize(), TransactionsCount);
}