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

#include "fs_ideas/platform_filesystem.hpp"
#include "wrapper/heap_block_device.hpp"

CoroUtils::Task<int> coroutineTask()
{
    int b = 32;

    co_return b;
}

void showFlashDeviceId()
{
    CoroUtils::Task<int> task = coroutineTask();
    int testValue = co_await task;
}
using TFilesystem = Platform::Fs::Holder<Wrapper::HeapBlockDevice<Wrapper::kBlockSize, Wrapper::kSectorsCount>>;
CoroUtils::VoidTask fileTest(TFilesystem& filesystem)
{

    auto file = filesystem.openFile("test.txt");
    constexpr auto kFileData = std::string_view("Hello world!");
    co_await file.write(
        {reinterpret_cast<const std::uint8_t*>(kFileData.data()), kFileData.size()});
    auto data = co_await file.read(kFileData.size());

    std::cout << std::string_view(reinterpret_cast<const char*>(data.data()), data.size());
}

int main()
{

    TFilesystem platformFilesystem;

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

    showFlashDeviceId();

    while (true)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
        CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
    }
    return 0;
}
