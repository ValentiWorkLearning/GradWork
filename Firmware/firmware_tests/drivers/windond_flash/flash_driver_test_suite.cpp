#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <random>

#include "flash_fixture.hpp"

#include <utils/CoroUtils.hpp>

TEST_F(FlashDriverTest, RequestJedecId)
{
    auto jedecId = CoroUtils::syncWait(flashDriver.requestJEDEDCId());
    constexpr std::uint32_t MagicTrashFromRawMemory = 13487565; //  For fun;
    EXPECT_EQ(jedecId, MagicTrashFromRawMemory);
}