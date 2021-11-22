#pragma once
#include "fs_common.hpp"
#include <lfs.h>
#include <string>
#include <utils/CoroUtils.hpp>
#include <memory>
#include "ih_block_device.hpp"

namespace Platform::Fs
{
class Holder
{
public:
    Holder(std::unique_ptr<Wrapper::IBlockDeviceEntity>&& platformBlockDevice);
    CoroUtils::Task<File> openFile(std::string_view path);

    void close(File* pFile);

private:
    lfs_config createLfsConfig();

private:
    Holder();

private:
    lfs_t m_fsInstance;
    std::unique_ptr<Wrapper::IBlockDeviceEntity> m_blockDeviceHolder;
};
} // namespace Platform::Fs
