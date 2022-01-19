#include <array>
#include <atomic>
#include <chrono>
#include <coroutine>
#include <cstdint>
#include <functional>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include <display/display_coro_compact_gc9a01.hpp>
#include <display/display_spi_common_coro.hpp>
#include <logger/logger_service.hpp>
#include <utils/CoroUtils.hpp>
#include <utils/coroutine/SyncWait.hpp>

#include <backends/spi_backend_desktop.hpp>
#include <spi/spi_wrapper_async_templated.hpp>

#include "st7789_draft.hpp"
#include <filesystem/platform_filesystem.hpp>
#include <filesystem/block_device_wrapper/heap_block_device.hpp>
#include <filesystem/block_device_wrapper/adaptor_block_device.hpp>

#include <spdlog/spdlog.h>

using TFilesystem = Platform::Fs::Holder<Wrapper::LogAdaptorBlockDevice<Wrapper::HeapBlockDevice<
    Wrapper::kBlockSize,
    Wrapper::kSectorsCount,
    Wrapper::kReadSize,
    Wrapper::kEraseSize>>>;

using TFile = Platform::Fs::File<TFilesystem>;

CoroUtils::VoidTask simpleRwTest(
    TFilesystem& filesystem,
    std::string_view fileName,
    std::string_view fileData)
{
    spdlog::warn("simpleRwTest begin");
    auto lfs = filesystem.fsInstance();
    {
        spdlog::warn("FILE open begin");
        auto filename = std::move(co_await filesystem.openFile(fileName));
        co_await filename.write(
            std::span(reinterpret_cast<const std::uint8_t*>(fileData.data()), fileData.size()));
        spdlog::warn("FILE open finalize");
    }

    std::vector<std::uint8_t> readFrom;
    readFrom.resize(fileData.size());

    {
        spdlog::warn("FILE read begin");
        auto holdedFile = std::move(co_await filesystem.openFile(fileName));
        auto resultRead = co_await holdedFile.read(std::span(readFrom.data(), fileData.size()));
        spdlog::warn("FILE read finalize");
    }

    auto kCompareStringView{
        std::string_view{reinterpret_cast<const char*>(readFrom.data()), readFrom.size()}};
    assert(fileData == kCompareStringView);
    spdlog::warn("simpleRwTest finalize");
}
CoroUtils::VoidTask fileTest(TFilesystem& filesystem)
{
    constexpr auto kFileData = std::string_view("Hello world!");
    simpleRwTest(filesystem, "helloworld.txt", kFileData);

    auto kNmeaDataExample = std::string_view{
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
    co_await simpleRwTest(filesystem, "nmeaData.txt", kNmeaDataExample);

    co_return;
}

int main()
{

    TFilesystem platformFilesystem;
    CoroUtils::syncWait(platformFilesystem.initializeFs());

    CoroUtils::syncWait(fileTest(platformFilesystem));

    using TSpiBus = Interface::SpiTemplated::SpiBus<Interface::SpiTemplated::SpiBusDesktopBackend>;

    using TDisplayDriver = DisplayDriver::GC9A01Compact<TSpiBus, 240, 240>;
    /*Display display{};
    display.fillRectangle(0, 0, 220, 220, nullptr);*/

    TDisplayDriver compactGc9A01;
    compactGc9A01.fillRectangle(0, 0, 0, 0, nullptr);
    compactGc9A01.initialize();

    // ST7789Coroutine displayCoro{
    //       Interface::Spi::createSpiBusAsync<Interface::Spi::SpiInstance::M1>()
    //    ,  240
    //    ,  240
    //};
    // displayCoro.fillRectangle(0, 0, 0, 0, nullptr);

    while (true)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
        CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
    }
    return 0;
}
