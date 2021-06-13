#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include "flash_fixture.hpp"

#include <array>
#include <utils/CoroUtils.hpp>
#include <utils/coroutine/SyncWait.hpp>

TEST_F(FlashDriverTest, RequestJedecId)
{
    EXPECT_CALL(getMockGpio(), setGpioLow()).Times(1);
    EXPECT_CALL(getMockGpio(), setGpioHigh()).Times(1);

    TDataStream ExpectedStream{std::byte(0xEF), std::byte(0x40), std::byte(0x18)};

    setReceivedSpiStream(ExpectedStream);

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

TEST_F(FlashDriverTest, RequestWriteBlock)
{

    EXPECT_CALL(getMockGpio(), setGpioLow()).Times(1);
    EXPECT_CALL(getMockGpio(), setGpioHigh()).Times(1);

    auto TransmitData{std::array<std::uint8_t, 7>{0xEF, 0xFF, 0x18, 0x19, 0x20, 0x21, 0x22}};

    constexpr std::uint32_t address{0x10'00};

    auto task = flashDriver.pageWrite(address, std::span(TransmitData.data(), TransmitData.size()));
    CoroUtils::syncWait(task);

    //EXPECT_EQ(jedecId, fToJedecId(ExpectedStream));
}