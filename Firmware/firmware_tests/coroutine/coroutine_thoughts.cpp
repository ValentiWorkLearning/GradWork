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

#include <backends/spi_backend_desktop.hpp>
#include <spi/spi_wrapper_async_templated.hpp>

#include "st7789_draft.hpp"

#include <lfs.h>

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

namespace Internals::Fs
{

class FilesystemPasskey
{
    friend class File;
    friend class Holder;

private:
    FilesystemPasskey()
    {
    }
    FilesystemPasskey(const FilesystemPasskey&) = default;
    FilesystemPasskey& operator=(const FilesystemPasskey&) = delete;
};

class File
{
public:
    explicit File(lfs_file_t fileHandle) : m_pFileHandle{fileHandle}
    {
    }
    ~File()
    {
        Holder::Instance().close(this);
    }
    CoroUtils::VoidTask write(std::span<const std::uint8_t> dataHolder)
    {
        co_return;
    }

    CoroUtils::Task<std::span<std::uint8_t>> read(std::size_t dataSize)
    {
        co_return {};
    }

    lfs_file_t nativeHandle(const FilesystemPasskey& passkey)
    {
        Meta::UnuseVar(passkey);
        return m_pFileHandle;
    }

private:
    lfs_file_t m_pFileHandle;
};
class Holder
{
public:
    static Holder& Instance()
    {
        static Holder fsHolder{};
        return fsHolder;
    }

    CoroUtils::Task<File> openFile(std::string_view path)
    {
        lfs_file_t file{};
        lfs_file_open(&m_fsInstance, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
        co_return File{file};
    }

    void close(File* pFile)
    {
        assert(pFile);
        if (!pFile)
            return;
        auto nativeHandle = pFile->nativeHandle(FilesystemPasskey{});
        lfs_file_close(&m_fsInstance, &nativeHandle);
    }

private:
    static constexpr inline lfs_config fsConfig{};

private:
    Holder()
    {
        auto error = lfs_mount(&m_fsInstance, &fsConfig);
        if (error)
        {
            lfs_format(&m_fsInstance, &fsConfig);
            lfs_mount(&m_fsInstance, &fsConfig);
        }
    }

private:
    lfs_t m_fsInstance;
};
} // namespace Internals::Fs

CoroUtils::VoidTask fileTest()
{
    auto file = co_await Internals::Fs::Holder::Instance().openFile("test.txt");
    constexpr auto kFileData = std::string_view("Hello world!");
    co_await file.write(
        {reinterpret_cast<const std::uint8_t*>(kFileData.data()), kFileData.size()});
    auto data = co_await file.read(kFileData.size());

    std::cout << std::string_view(reinterpret_cast<const char*>(data.data()), data.size());
}

int main()
{
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
