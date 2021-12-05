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
template <typename TFSHolder> class File;

template <typename TBlockDevice> class Holder;

class FilesystemPasskey
{
    template <typename TFSHolder> friend class File;

    template <typename TBlockDevice> friend class Holder;

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
    constexpr Holder()noexcept
    {
        m_fsConfig = createLfsConfig();
        auto error = lfs_mount(&m_fsInstance, &m_fsConfig);
        if (error)
        {
            lfs_format(&m_fsInstance, &m_fsConfig);
            lfs_mount(&m_fsInstance, &m_fsConfig);
        }
    }
    constexpr auto fsInstance() noexcept
    {
        return m_fsInstance;
    }
    File<This_t> openFile(std::string_view path)noexcept
    {
        lfs_file_t file{};
        lfs_file_open(&m_fsInstance, &file, path.data(), LFS_O_RDWR | LFS_O_CREAT);
        return File{file, this};
    }

    void close(File<This_t>* pFile)noexcept
    {
        assert(pFile);
        if (!pFile)
            return;
        auto nativeHandle = pFile->nativeHandle(FilesystemPasskey{});
        lfs_file_close(&m_fsInstance, &nativeHandle);
    }

    constexpr TBlockDeviceEntity& getBlockDevice()noexcept
    {
        return m_blockDeviceHolder;
    }

private:
private:
    constexpr static int readCall(
        const struct lfs_config* c,
        lfs_block_t block,
        lfs_off_t off,
        void* buffer,
        lfs_size_t size)noexcept
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        pThis->getBlockDevice().read(
            static_cast<std::uint8_t*>(buffer), block * c->block_size + off, size);
        return LFS_ERR_OK;
    }

    constexpr static int progCall(
        const struct lfs_config* c,
        lfs_block_t block,
        lfs_off_t off,
        const void* buffer,
        lfs_size_t size)noexcept
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        pThis->getBlockDevice().write(
            (block * c->block_size + off), reinterpret_cast<const std::uint8_t*>(buffer), size);

        return LFS_ERR_OK;
    }

    constexpr static int eraseCall(const struct lfs_config* c, lfs_block_t block)noexcept
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        return LFS_ERR_OK;
    }

    constexpr static int syncCall(const struct lfs_config* c)noexcept
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        return LFS_ERR_OK;
    }

private:
    constexpr lfs_config createLfsConfig() noexcept
    {
        constexpr std::size_t kBlockCycles = 500;
        return lfs_config{
            .context = this,
            .read = readCall,
            .prog = progCall,
            .erase = eraseCall,
            .sync = syncCall,

            .read_size = m_blockDeviceHolder.getReadSize(),
            .prog_size = m_blockDeviceHolder.getProgSize(),

            .block_size = m_blockDeviceHolder.getBlockSize(),
            .block_count = m_blockDeviceHolder.getBlocksCount(),

            .block_cycles = kBlockCycles,
            .cache_size = m_blockDeviceHolder.getBlockSize(),
            .lookahead_size = m_blockDeviceHolder.getBlockSize(),

            .read_buffer = readBuffer.data(),
            .prog_buffer = writeBuffer.data(),
            .lookahead_buffer = lookaheadBuffer.data()};
    }

private:
    static constexpr inline std::size_t FsArraySize = 512;
    using TDataHolder = std::array<std::uint8_t, FsArraySize>;

private:
    lfs_config m_fsConfig;
    lfs_t m_fsInstance;
    TBlockDeviceEntity m_blockDeviceHolder;
    TDataHolder readBuffer;
    TDataHolder writeBuffer;
    TDataHolder lookaheadBuffer;
};

template <typename TFilesystemHolder> class File
{
public:
    explicit constexpr File()noexcept = default;
    explicit constexpr File(lfs_file_t fileHandle, TFilesystemHolder* pFsHolder)noexcept
        : m_pFileHandle{fileHandle}, m_pFsHolder{pFsHolder}
    {
    }
    ~File()
    {
        if (m_pFsHolder)
            m_pFsHolder->close(this);
    }
    CoroUtils::VoidTask write(std::span<const std::uint8_t> dataHolder)noexcept
    {
        auto fsInstance = m_pFsHolder->fsInstance();
        lfs_file_write(&fsInstance, &m_pFileHandle, dataHolder.data(), static_cast<lfs_size_t>(dataHolder.size()));
        co_return;
    }

    CoroUtils::Task<std::span<std::uint8_t>> read(std::size_t dataSize)noexcept
    {
        co_return {};
    }

    lfs_file_t nativeHandle(const FilesystemPasskey& passkey)noexcept
    {
        Meta::UnuseVar(passkey);
        return m_pFileHandle;
    }

private:
    lfs_file_t m_pFileHandle;
    TFilesystemHolder* m_pFsHolder;
};
} // namespace Platform::Fs
