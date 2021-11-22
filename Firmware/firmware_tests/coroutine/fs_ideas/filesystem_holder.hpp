#pragma once
#include "ih_block_device.hpp"
#include <lfs.h>
#include <memory>
#include <string>
#include <utils/CoroUtils.hpp>

#include <cstdint>
#include <span>
#include <utils/MetaUtils.hpp>

namespace Platform::Fs
{
template<typename TFSHolder>
class File;

template<typename TBlockDevice>
class Holder;

class FilesystemPasskey
{
    template <typename TFSHolder>
    friend class File;

    template <typename TBlockDevice>
    friend class Holder;

private:
    FilesystemPasskey()
    {
    }
    FilesystemPasskey(const FilesystemPasskey&) = default;
    FilesystemPasskey& operator=(const FilesystemPasskey&) = delete;
};
template <typename TBlockDeviceEntity> class Holder
{
public:
    using This_t = Holder<TBlockDeviceEntity>;
public:
    constexpr Holder()
    {
        auto fsConfig{createLfsConfig()};
        auto error = lfs_mount(&m_fsInstance, &fsConfig);
        if (error)
        {
            lfs_format(&m_fsInstance, &fsConfig);
            lfs_mount(&m_fsInstance, &fsConfig);
        }
    }
    CoroUtils::Task<File<This_t>> openFile(std::string_view path)
    {
        lfs_file_t file{};
        lfs_file_open(&m_fsInstance, &file, path.data(), LFS_O_RDWR | LFS_O_CREAT);
        co_return File{file, this};
    }

    void close(File<This_t>* pFile)
    {
        assert(pFile);
        if (!pFile)
            return;
        auto nativeHandle = pFile->nativeHandle(FilesystemPasskey{});
        lfs_file_close(&m_fsInstance, &nativeHandle);
    }

private:

private:
    static int readCall(
        const struct lfs_config* c,
        lfs_block_t block,
        lfs_off_t off,
        void* buffer,
        lfs_size_t size)
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        return LFS_ERR_OK;
    }

    static int progCall(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer,
        lfs_size_t size)
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        return LFS_ERR_OK;
    }

    static int eraseCall(const struct lfs_config* c, lfs_block_t block)
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        return LFS_ERR_OK;
    }

    static int syncCall(const struct lfs_config* c)
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        return LFS_ERR_OK;
    }

private :
    lfs_config createLfsConfig()
    {
        constexpr std::size_t kBufferDefaultSize = 16;
        constexpr std::size_t kBlockCycles = 500;
        return lfs_config
        {
            .context = this,
            .read = readCall,
            .prog = progCall,
            .erase = eraseCall,
            .sync = syncCall,

            .read_size = kBufferDefaultSize, .prog_size = kBufferDefaultSize,

            .block_size = m_blockDeviceHolder.getBlockSize(),
            .block_count = m_blockDeviceHolder.getBlocksCount(),

            .block_cycles = kBlockCycles, .cache_size = kBufferDefaultSize,
            .lookahead_size = kBufferDefaultSize,
        };
    }

private:
    lfs_t m_fsInstance;
    TBlockDeviceEntity m_blockDeviceHolder;
};

template <typename TFilesystemHolder> class File
{
public:
    explicit File() = default;
    explicit File(lfs_file_t fileHandle, TFilesystemHolder* pFsHolder)
        : m_pFileHandle{fileHandle}, m_pFsHolder{pFsHolder}
    {
    }
    ~File()
    {
        if (m_pFsHolder)
            m_pFsHolder->close(this);
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
    TFilesystemHolder* m_pFsHolder;
};
} // namespace Platform::Fs
