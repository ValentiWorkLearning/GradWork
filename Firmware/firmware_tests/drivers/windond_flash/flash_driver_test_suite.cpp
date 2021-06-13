#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include "flash_fixture.hpp"

#include <utils/CoroUtils.hpp>
#include <utils/coroutine/SyncWait.hpp>

TEST_F(FlashDriverTest, RequestJedecId)
{
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