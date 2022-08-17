#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include "flash_fixture.hpp"

#include <array>
#include <utils/CoroUtils.hpp>
#include <utils/coroutine/SyncWait.hpp>

using ::testing::ContainerEq;
using ::testing::Return;

namespace Testing::FlashCommandStubs
{
constexpr std::size_t WriteEnableCommandLength = 1;
constexpr const std::array<std::uint8_t, WriteEnableCommandLength> writeEnableCommand{
    WindbondCommandSet::WriteEnable};

constexpr std::size_t ReadStatusCommandLength = 1;
constexpr const std::array<std::uint8_t, ReadStatusCommandLength> readStatusRegisterCommand{
    WindbondCommandSet::ReadStatusRegister1};

constexpr std::uint32_t address{0x10'00};

constexpr std::size_t ProgramPageCommandLength = 4;

constexpr const std::array<std::uint8_t, ProgramPageCommandLength> pageProgramCommand{
    WindbondCommandSet::PageProgram,
    static_cast<std::uint8_t>((address & 0x00'FF'00'00) >> 16),
    static_cast<std::uint8_t>((address & 0x00'00'FF'00) >> 8),
    static_cast<std::uint8_t>(address & 0x00'00'00'FF)};

constexpr const std::array<std::uint8_t, ProgramPageCommandLength> erase4KSectorCommand{
    WindbondCommandSet::SectorErase4KB,
    static_cast<std::uint8_t>((address & 0x00'FF'00'00) >> 16),
    static_cast<std::uint8_t>((address & 0x00'00'FF'00) >> 8),
    static_cast<std::uint8_t>(address & 0x00'00'00'FF)};
} // namespace Testing::FlashCommandStubs

namespace Testing::Utils
{
template <typename TByteSequence>
constexpr std::span<const std::uint8_t> make_span(const TByteSequence& toSpan)
{
    return std::span(reinterpret_cast<const std::uint8_t*>(toSpan.data()), toSpan.size());
}
} // namespace Testing::Utils

TEST_F(FlashDriverTest, RequestJedecId)
{
    EXPECT_CALL(getMockGpio(), setGpioLow()).Times(1);
    EXPECT_CALL(getMockGpio(), setGpioHigh()).Times(1);

    TDataStream ExpectedStream{std::byte(0xEF), std::byte(0x40), std::byte(0x18)};

    EXPECT_CALL(spiMockAccess(), receivedData)
        .Times(1)
        .WillOnce(Return(std::span(
            reinterpret_cast<const std::uint8_t*>(ExpectedStream.data()), ExpectedStream.size())));

    auto fToJedecId = [](const TDataStream& _jedecId) {
        std::uint32_t result{};
        result |= std::to_integer<std::uint32_t>(_jedecId[0]) << 16;
        result |= std::to_integer<std::uint32_t>(_jedecId[1]) << 8;
        result |= std::to_integer<std::uint32_t>(_jedecId[2]);

        return result;
    };

    auto jedecId = CoroUtils::syncWait(flashDriver.requestJEDEDCId());
    EXPECT_EQ(jedecId, fToJedecId(ExpectedStream));
}

MATCHER_P(SpanChecker, spanItem, "Span content equals")
{
    const bool isEqual = std::ranges::equal(spanItem, std::get<0>(arg));
    return isEqual;
}
TEST_F(FlashDriverTest, RequestWriteBlock)
{

    EXPECT_CALL(getMockGpio(), setGpioLow()).Times(6);
    EXPECT_CALL(getMockGpio(), setGpioHigh()).Times(6);

    auto TransmitData{std::array<std::uint8_t, 7>{0xEF, 0xFF, 0x18, 0x19, 0x20, 0x21, 0x22}};

    testing::Sequence sequence;

    // https://gist.github.com/cppengineer/f1b6bc0f04ac7c29e963364f2c564a5e

    const auto writeEnableSpan =
        Testing::Utils::make_span(Testing::FlashCommandStubs::writeEnableCommand);

    TDataStream ExpectedStream{std::byte(0xEF), std::byte(0x40), std::byte(0x18)};
    TDataStream kDummyByte{std::byte(0x00)};

    EXPECT_CALL(spiMockAccess(), receivedData)
        .Times(3)
        .WillOnce(Return(Testing::Utils::make_span(kDummyByte)));

    const auto kEraseSectorCommandSpan =
        Testing::Utils::make_span(Testing::FlashCommandStubs::erase4KSectorCommand);

    auto fIsBusyChecker = [this, &sequence, kDummyByte] {
        EXPECT_CALL(spiMockAccess(), sentData)
            .With(SpanChecker(Testing::FlashCommandStubs::readStatusRegisterCommand))
            .Times(1)
            .InSequence(sequence);

        EXPECT_CALL(spiMockAccess(), sentData)
            .With(SpanChecker(Testing::Utils::make_span(kDummyByte)))
            .Times(1)
            .InSequence(sequence);
    };

    {

        EXPECT_CALL(spiMockAccess(), sentData)
            .With(SpanChecker(writeEnableSpan))
            .Times(1)
            .InSequence(sequence);
        fIsBusyChecker();
    }

    {
        EXPECT_CALL(spiMockAccess(), sentData)
            .With(SpanChecker(kEraseSectorCommandSpan))
            .Times(1)
            .InSequence(sequence);
        fIsBusyChecker();
    }

    {

        EXPECT_CALL(spiMockAccess(), sentData)
            .With(SpanChecker(Testing::FlashCommandStubs::pageProgramCommand))
            .Times(1)
            .InSequence(sequence);

        EXPECT_CALL(spiMockAccess(), sentData)
            .With(SpanChecker(Testing::Utils::make_span(TransmitData)))
            .Times(1)
            .InSequence(sequence);

        fIsBusyChecker();
    }

    auto task = flashDriver.pageWrite(
        Testing::FlashCommandStubs::address, Testing::Utils::make_span(TransmitData));
    CoroUtils::syncWait(task);
}

TEST_F(FlashDriverTest, RequestReadBlock)
{

    EXPECT_CALL(getMockGpio(), setGpioLow()).Times(2);
    EXPECT_CALL(getMockGpio(), setGpioHigh()).Times(2);

    using TStream = std::array<std::uint8_t, 7>;

    auto ReceiveData{TStream{0xEF, 0xFF, 0x18, 0x19, 0x20, 0x21, 0x22}};

    auto Dummy{TStream{}};

    TDataStream kDummyByte{std::byte(0x00)};

    EXPECT_CALL(spiMockAccess(), receivedData)
        .WillOnce(Return(Testing::Utils::make_span(kDummyByte)))
        .WillOnce(Return(std::span(
            reinterpret_cast<const std::uint8_t*>(ReceiveData.data()), ReceiveData.size())));

    constexpr std::uint32_t address{0x10'00};

    constexpr std::size_t ReadCommandLength = 4;
    constexpr const std::array<std::uint8_t, ReadCommandLength> readCommand{
        WindbondCommandSet::ReadData,
        static_cast<std::uint8_t>((address & 0x00'FF'00'00) >> 16),
        static_cast<std::uint8_t>((address & 0x00'00'FF'00) >> 8),
        static_cast<std::uint8_t>(address & 0x00'00'00'FF)};

    testing::Sequence sequence;

    // https://gist.github.com/cppengineer/f1b6bc0f04ac7c29e963364f2c564a5e

    const auto DummySpan = std::span<const std::uint8_t>(Dummy.data(), Dummy.size());

    const auto ReadDataSpan = std::span<const std::uint8_t>(readCommand.data(), readCommand.size());

    EXPECT_CALL(spiMockAccess(), sentData)
        .With(SpanChecker(Testing::FlashCommandStubs::readStatusRegisterCommand))
        .Times(1)
        .InSequence(sequence);

    EXPECT_CALL(spiMockAccess(), sentData)
        .With(SpanChecker(Testing::Utils::make_span(kDummyByte)))
        .Times(1)
        .InSequence(sequence);

    EXPECT_CALL(spiMockAccess(), sentData)
        .With(SpanChecker(ReadDataSpan))
        .Times(1)
        .InSequence(sequence);

    EXPECT_CALL(spiMockAccess(), sentData)
        .With(SpanChecker(std::span(DummySpan.data(), DummySpan.size())))
        .Times(1)
        .InSequence(sequence);

    auto task = flashDriver.requestReadBlock(address, ReceiveData.size());
    auto readSpan{CoroUtils::syncWait(task)};

    EXPECT_TRUE(std::ranges::equal(readSpan, ReceiveData));
}