#include "filesystem_fixture.hpp"
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utils/coroutine/SyncWait.hpp>

constexpr auto HelloWorldData =
    FilesystemParamInterfaceData{.fileData = "Hello world!", .filename = "helloworld.txt"};

constexpr auto kNmeaDataExample = std::string_view{
    "$GPGSA,A,1,,,,,,,,,,,,,,,* 1E\n"
    "$GPGSV,1,1,0,,,,,,,,,,,,,,,,* 49\n"
    "$GPRMC,114811.00,A,5548.2054190,N,03732.8518300,E,0.22,0.00,210618,0.0,E,A * 30\n"
    "$GPGGA,114811.00,5548.2054190,N,03732.8518300,E,1,06,1.0,179.534,M,14.753,M,0.0,* 45\n"
    "$GPGSA,A,3,02,21,25,26,31,,,,,,,,5.4,1.2,5.3,1 * 2B\n"
    "$GAGSA,A,3,30,,,,,,,,,,,,0.0,0.0,0.0,3 * 3F\n"
    "$GPGSV,2,1,05,02,23,059,28,21,30,222,32,25,41,166,35,26,36,303,34,1 * 67\n"
    "$GPGSV,2,2,05,31,27,254,34,,,,,,,,,,,,,1 * 52\n"
    "$GAGSV,1,1,01,30,23,183,33,,,,,,,,,,,,,7 * 4A\n"
    "$GPRMC,114812.00,A,5548.2052305,N,03732.8513810,E,0.17,0.00,210618,0.0,E,A * 3C\n"
    "$GPGGA,114812.00,5548.2052305,N,03732.8513810,E,1,06,1.0,178.149,M,14.753,M,0.0,* 40\n"
    "$GPGSA,A,3,02,21,25,26,31,,,,,,,,5.4,1.2,5.3,1 * 2B\n"
    "$GAGSA,A,3,30,,,,,,,,,,,,0.0,0.0,0.0,3 * 3F\n"
    "$GPGSV,2,1,05,02,23,059,28,21,30,222,31,25,41,166,36,26,36,303,34,1 * 67\n"
    "$GPGSV,2,2,05,31,27,254,34,,,,,,,,,,,,,1 * 52\n"
    "$GAGSV,1,1,01,30,23,183,32,,,,,,,,,,,,,7 * 4B\n"
    "$GPRMC,114813.00,A,5548.2048307,N,03732.8514121,E,0.28,0.00,210618,0.0,E,A * 34\n"
    "$GPGGA,114813.00,5548.2048307,N,03732.8514121,E,1,06,1.0,172.326,M,14.753,M,0.0,* 45\n"
    "$GPGSA,A,3,02,21,25,26,31,,,,,,,,5.4,1.2,5.3,1 * 2B\n"
    "$GAGSA,A,3,30,,,,,,,,,,,,0.0,0.0,0.0,3 * 3F\n"
    "$GPGSV,2,1,05,02,23,059,28,21,31,222,32,25,41,166,36,26,36,303,34,1 * 65\n"
    "$GPGSV,2,2,05,31,27,254,34,,,,,,,,,,,,,1 * 52\n"
    "$GAGSV,1,1,01,30,23,183,32,,,,,,,,,,,,,7 * 4B\n"
    "$GPRMC,114814.00,A,5548.2047440,N,03732.8516481,E,0.19,0.00,210618,0.0,E,A * 37\n"
    "$GPGGA,114814.00,5548.2047440,N,03732.8516481,E,1,06,1.0,172.488,M,14.753,M,0.0,* 47\n"
    "$GPGSA,A,3,02,21,25,26,31,,,,,,,,5.4,1.2,5.3,1 * 2B\n"
    "$GAGSA,A,3,30,,,,,,,,,,,,0.0,0.0,0.0,3 * 3F\n"
    "$GPGSV,2,1,05,02,23,059,28,21,31,222,32,25,41,166,35,26,36,303,34,1 * 66\n"
    "$GPGSV,2,2,05,31,27,254,34,,,,,,,,,,,,,1 * 52\n"
    "$GAGSV,1,1,01,30,23,183,32,,,,,,,,,,,,,7 * 4B\n"

};

constexpr auto NmeaData =
    FilesystemParamInterfaceData{.fileData = kNmeaDataExample, .filename = "nmea_data.txt"};

TEST_P(FilesystemTopLevelTestFixture, CheckFileReadWriteProcedure)
{
    auto lfs = m_testFilesystem.fsInstance();
    {
        auto filePath = GetParam().filename;
        auto filename = std::move(CoroUtils::syncWait(m_testFilesystem.openFile(filePath)));
        CoroUtils::syncWait(filename.write(std::span(
            reinterpret_cast<const std::uint8_t*>(GetParam().fileData.data()),
            GetParam().fileData.size())));
    }

    std::vector<std::uint8_t> readFrom;
    readFrom.resize(GetParam().fileData.size());

    {
        auto holdedFile =
            std::move(CoroUtils::syncWait(m_testFilesystem.openFile(GetParam().filename)));
        auto resultRead = CoroUtils::syncWait(
            holdedFile.read(std::span(readFrom.data(), GetParam().fileData.size())));
    }

    auto kCompareStringView{
        std::string_view{reinterpret_cast<const char*>(readFrom.data()), readFrom.size()}};
    EXPECT_EQ(kCompareStringView, GetParam().fileData);
}

INSTANTIATE_TEST_SUITE_P(
    FilesystemTopLevelTesting,
    FilesystemTopLevelTestFixture,
    ::testing::Values(HelloWorldData, NmeaData));