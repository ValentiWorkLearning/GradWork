#include "filesystem_fixture.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <utils/coroutine/SyncWait.hpp>


//https://stackoverflow.com/questions/56115790/gtest-parametrized-tests-for-different-types
// http://www.ashermancinelli.com/gtest-type-val-param

TYPED_TEST_SUITE_P(FilesystemTopLevelTestFixture);


TYPED_TEST_P(FilesystemTopLevelTestFixture, CheckFileReadWriteProcedure)
{
    for (auto const& testParamData : this->m_params.testData)
    {
        auto& filesystemInstance = this->m_testFilesystem;
        auto lfs = filesystemInstance.fsInstance();
        {
            auto filePath = testParamData.filename;
            auto filename = std::move(CoroUtils::syncWait(filesystemInstance.openFile(filePath)));
            CoroUtils::syncWait(filename.write(std::span(
                reinterpret_cast<const std::uint8_t*>(testParamData.fileData.data()),
                testParamData.fileData.size())));
        }

        std::vector<std::uint8_t> readFrom;
        readFrom.resize(testParamData.fileData.size());

        {
            auto holdedFile = std::move(CoroUtils::syncWait(filesystemInstance.openFile(testParamData.filename)));
            auto resultRead = CoroUtils::syncWait(
                holdedFile.read(std::span(readFrom.data(), testParamData.fileData.size())));
        }

        auto kCompareStringView{
            std::string_view{reinterpret_cast<const char*>(readFrom.data()), readFrom.size()}};
        EXPECT_EQ(kCompareStringView, testParamData.fileData);
    }
}


REGISTER_TYPED_TEST_SUITE_P(FilesystemTopLevelTestFixture, CheckFileReadWriteProcedure);

using TTestFilesystems = ::testing::Types<THeapFilesystem,TWrappedFilesystem>;
INSTANTIATE_TYPED_TEST_SUITE_P(FilesystemTests, FilesystemTopLevelTestFixture, TTestFilesystems);
