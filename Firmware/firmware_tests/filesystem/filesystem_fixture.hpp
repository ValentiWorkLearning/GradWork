#pragma once
#include <gtest/gtest.h>

#include <filesystem/block_device_wrapper/adaptor_block_device.hpp>
#include <filesystem/block_device_wrapper/heap_block_device.hpp>
#include <filesystem/platform_filesystem.hpp>

#include <utils/coroutine/SyncWait.hpp>

#include <filesystem/block_device_wrapper/combiner_block_device.hpp>
#include <filesystem/block_device_wrapper/spi_block_device.hpp>

#include <spi/spi_wrapper_async_templated.hpp>
#include <windbondflash/winbond_flash_templated.hpp>

// TODO Fix include more clearly
#include "../drivers/spi/mock_gpio.hpp"
#include "../drivers/spi/spi_fake_backend.hpp"
#include "filesystem_test_data.hpp"

using TFlashTestDriver = ExternalFlash::WinbondFlashDriver<
    Interface::SpiTemplated::SpiBus<Testing::Spi::SpiBusBackendStub>>;

using TSpiFlashBlockDevice = Filesystem::BlockDevice::SpiFlashBlockDevice<TFlashTestDriver>;

using TLogHeapBlockDevice =
    Filesystem::BlockDevice::LogAdaptorBlockDevice<Filesystem::BlockDevice::HeapBlockDevice<
        Filesystem::BlockDevice::kBlockSize,
        Filesystem::BlockDevice::kSectorsCount,
        Filesystem::BlockDevice::kReadSize,
        Filesystem::BlockDevice::kEraseSize>>;

using TCombinedBlockDevice =
    Filesystem::BlockDevice::CombinerBlockDevice<TLogHeapBlockDevice, TSpiFlashBlockDevice>;

using TWrappedFilesystem = Platform::Fs::Holder<TCombinedBlockDevice>;

using THeapFilesystem = Platform::Fs::Holder<
    Filesystem::BlockDevice::LogAdaptorBlockDevice<Filesystem::BlockDevice::HeapBlockDevice<
        Filesystem::BlockDevice::kBlockSize,
        Filesystem::BlockDevice::kSectorsCount,
        Filesystem::BlockDevice::kReadSize,

        Filesystem::BlockDevice::kEraseSize>>>;

template <typename TFilesystem> struct TestParamPlaceholder
{
    using THoldedFilesystem = TFilesystem;
    std::vector<FilesystemParamInterfaceData> testData;
};

static std::tuple<TestParamPlaceholder<TWrappedFilesystem>, TestParamPlaceholder<THeapFilesystem>>
    kFilesystemTestParams{
        {{HelloWorldData, NmeaData}},
        {{HelloWorldData, NmeaData}},
    };

// http://www.ashermancinelli.com/gtest-type-val-param
template <typename Filesystem> class FilesystemTopLevelTestFixture : public ::testing::Test
{

public:
    FilesystemTopLevelTestFixture()
        : m_params{std::get<TestParamPlaceholder<Filesystem>>(kFilesystemTestParams)}
    {
    }

protected:
    void SetUp() override
    {
        CoroUtils::syncWait(m_testFilesystem.initializeFs());
    }

protected:
    TestParamPlaceholder<Filesystem> m_params;
    Filesystem m_testFilesystem;
};