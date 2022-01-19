#pragma once
#include <gtest/gtest.h>

#include <filesystem/platform_filesystem.hpp>
#include <filesystem/block_device_wrapper/heap_block_device.hpp>
#include <filesystem/block_device_wrapper/adaptor_block_device.hpp>


#include <utils/coroutine/SyncWait.hpp>

struct FilesystemParamInterfaceData
{
    std::string_view fileData;
    std::string_view filename;
};

class FilesystemTopLevelTestFixture
    : public ::testing::Test
    , public ::testing::WithParamInterface<FilesystemParamInterfaceData>
{

public:

    using TFilesystem = Platform::Fs::Holder<Wrapper::LogAdaptorBlockDevice<Wrapper::HeapBlockDevice<
        Wrapper::kBlockSize,
        Wrapper::kSectorsCount,
        Wrapper::kReadSize,
        Wrapper::kEraseSize>>>;

    using TFile = Platform::Fs::File<TFilesystem>;

protected:
    void SetUp() override
    {
        CoroUtils::syncWait(m_testFilesystem.initializeFs());
    }

 

protected:
    TFilesystem m_testFilesystem;
};