#include "filesystem_holder.hpp"
#include "file_handle.hpp"

namespace Platform::Fs
{

Holder::Holder(std::unique_ptr<Wrapper::IBlockDeviceEntity>&& blockDeviceEntity)
    : m_fsInstance{}, m_blockDeviceHolder{std::move(blockDeviceEntity)}
{
    auto fsConfig{ createLfsConfig() };
    auto error = lfs_mount(&m_fsInstance, &fsConfig);
    if (error)
    {
        lfs_format(&m_fsInstance, &fsConfig);
        lfs_mount(&m_fsInstance, &fsConfig);
    }
}
CoroUtils::Task<File> Holder::openFile(std::string_view path)
{
    lfs_file_t file{};
    lfs_file_open(&m_fsInstance, &file, path.data(), LFS_O_RDWR | LFS_O_CREAT);
    co_return File{file, this};
}
void Holder::close(File* pFile)
{
    assert(pFile);
    if (!pFile)
        return;
    auto nativeHandle = pFile->nativeHandle(FilesystemPasskey{});
    lfs_file_close(&m_fsInstance, &nativeHandle);
}
lfs_config Holder::createLfsConfig()
{
    constexpr std::size_t kBufferDefaultSize = 16;
    constexpr std::size_t kBlockCycles = 500;
    return lfs_config
    {
        .read = m_blockDeviceHolder->readCallback(),
        .prog = m_blockDeviceHolder->progCallback(),
        .erase = m_blockDeviceHolder->eraseCallback(),
        .sync = m_blockDeviceHolder->syncCallback(),

        .read_size = kBufferDefaultSize,
        .prog_size = kBufferDefaultSize,

        .block_size = m_blockDeviceHolder->getBlockSize(),
        .block_count = m_blockDeviceHolder->getBlocksCount(),

        .block_cycles = kBlockCycles,
        .cache_size = kBufferDefaultSize,
        .lookahead_size = kBufferDefaultSize,
    };
}
} // namespace Platform::Fs