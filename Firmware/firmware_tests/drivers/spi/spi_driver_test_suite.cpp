#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include "spi_driver_fixture.hpp"

#include <utils/coroutine/SyncWait.hpp>

constexpr inline std::uint16_t Null = 0;
constexpr inline std::uint16_t SmallerThanSingleDmaTransaction =
    SpiDriverTest::TTestDriver::DmaBufferSize - 2;
constexpr inline std::uint16_t EqualsToSingleDmaTransaction =
    SpiDriverTest::TTestDriver::DmaBufferSize;
constexpr inline std::uint16_t ThreeDmaTransactions = EqualsToSingleDmaTransaction * 3;
constexpr inline std::uint16_t SingleDmaAndChunk =
    EqualsToSingleDmaTransaction + SmallerThanSingleDmaTransaction;
constexpr inline std::uint16_t ThreeDmaAndChunk =
    ThreeDmaTransactions + SmallerThanSingleDmaTransaction;
constexpr inline std::uint16_t StressChunked =
    ThreeDmaTransactions * 10 + SmallerThanSingleDmaTransaction;

TEST_F(SpiDriverTest, ExpectAnyTransmissionOccured)
{
    static constexpr std::byte DataBlock{223};
    static const TDataStream ExpectedStream{DataBlock};

    CoroUtils::syncWait(sendChunk(
        reinterpret_cast<const std::uint8_t*>(ExpectedStream.data()), ExpectedStream.size()));

    constexpr size_t TransactionsCount = 1;

    EXPECT_EQ(testSpiDriver.getBackendImpl().getTransactionsSize(), TransactionsCount);
    EXPECT_EQ(TransactionsToDataStream(), ExpectedStream);
}

TEST_P(SpiDriverTest, CheckRandomSequenceWithLengthTransmissionCorrect)
{
    const std::uint16_t TransactionLength{std::get<0>(GetParam())};
    TDataStream ExpectedStream{TransactionLength};

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(0x00, 0xFF);
    std::ranges::generate(ExpectedStream, [&distribution, generator]() mutable {
        return std::byte(distribution(generator));
    });

    co_await sendChunk(
        reinterpret_cast<const std::uint8_t*>(ExpectedStream.data()), ExpectedStream.size());
    EXPECT_EQ(TransactionsToDataStream(), ExpectedStream);
}

TEST_F(SpiDriverTest, CheckXferTransaction)
{
    constexpr std::uint8_t ReadUniqueId = 0x4B;
    constexpr std::uint8_t ReceivedDataLength = 8;

    auto& transmitBuffer = testSpiDriver.getDmaBufferTransmit();
    std::ranges::fill_n(transmitBuffer.begin(), ReceivedDataLength + 1, 0x00);
    transmitBuffer[0] = ReadUniqueId;

    TDataStream ExpectedStream{ReceivedDataLength};

    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_int_distribution<> distribution(0x00, 0xFF);

    std::ranges::generate(ExpectedStream, [&distribution, generator]() mutable {
        return std::byte(distribution(generator));
    });

    testSpiDriver.getBackendImpl().setReceivedStream(ExpectedStream);

    auto receivedStreamSpan = CoroUtils::syncWait(xferTransaction(
        std::span(
            reinterpret_cast<const std::uint8_t*>(transmitBuffer.data()), ReceivedDataLength + 1),
        std::span(testSpiDriver.getDmaBufferReceive().data(), ReceivedDataLength)));

    TDataStream receivedStream;
    std::ranges::transform(
        receivedStreamSpan, std::back_inserter(receivedStream), [](auto receivedItem) {
            return static_cast<std::byte>(receivedItem);
        });

    EXPECT_EQ(ExpectedStream, receivedStream);
}

INSTANTIATE_TEST_SUITE_P(
    SpiDriverTesting,
    SpiDriverTest,
    ::testing::Values(
        std::make_tuple(Null, "Null"),
        std::make_tuple(SmallerThanSingleDmaTransaction, "SmallerThanSingleDmaTransaction"),
        std::make_tuple(EqualsToSingleDmaTransaction, "EqualsToSingleDmaTransaction"),
        std::make_tuple(ThreeDmaTransactions, "ThreeDmaTransactions"),
        std::make_tuple(SingleDmaAndChunk, "SingleDmaAndChunk"),
        std::make_tuple(ThreeDmaAndChunk, "ThreeDmaAndChunk"),
        std::make_tuple(StressChunked, "StressChunked")),
    [](const auto& testParam) {
        const auto& suiteName = std::get<1>(testParam.param);
        return std::string(suiteName.data());
    });