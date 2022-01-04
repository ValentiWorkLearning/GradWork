#pragma once
#include "ih_block_device.hpp"
#include <lfs.h>
#include <memory>
#include <string>
#include <utils/CoroUtils.hpp>

#include <cstdint>
#include <span>
#include <utils/MetaUtils.hpp>

#include <spdlog/spdlog.h>

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
    constexpr Holder() noexcept
    {
        m_fsConfig = createLfsConfig();
        auto error = lfs_mount(&m_fsInstance, &m_fsConfig);
        if (error)
        {
            lfs_format(&m_fsInstance, &m_fsConfig);
            lfs_mount(&m_fsInstance, &m_fsConfig);
        }
    }

    constexpr decltype(auto) fsInstance() noexcept
    {
        return &m_fsInstance;
    }
    File<This_t> openFile(std::string_view path) noexcept
    {
        File<This_t> retFile{&m_fsInstance};
        lfs_file_open(
            &m_fsInstance,
            retFile.nativeHandle(FilesystemPasskey{}),
            path.data(),
            LFS_O_RDWR | LFS_O_CREAT);

        return retFile;
    }

    constexpr TBlockDeviceEntity& getBlockDevice() noexcept
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
        lfs_size_t size) noexcept
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
        lfs_size_t size) noexcept
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        pThis->getBlockDevice().write(
            (block * c->block_size + off), reinterpret_cast<const std::uint8_t*>(buffer), size);

        return LFS_ERR_OK;
    }

    constexpr static int eraseCall(const struct lfs_config* c, lfs_block_t block) noexcept
    {
        auto pThis = reinterpret_cast<This_t*>(c->context);
        return LFS_ERR_OK;
    }

    constexpr static int syncCall(const struct lfs_config* c) noexcept
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
    explicit constexpr File(lfs_t* pFsHolder) noexcept
        : m_pFileHandle{std::make_unique<lfs_file_t>()}, m_pFsHolder{pFsHolder}
    {
    }

    constexpr File(File&& otherHandle) noexcept
        : m_pFileHandle{std::move(otherHandle.m_pFileHandle)}
        , m_pFsHolder{std::exchange(otherHandle.m_pFsHolder, nullptr)}
    {
    }

    ~File()
    {
        if (!m_pFsHolder)
            return;

        lfs_file_close(m_pFsHolder, m_pFileHandle.get());
        spdlog::warn("~File::File()");
    }

    CoroUtils::VoidTask write(std::span<const std::uint8_t> dataHolder) noexcept
    {
        lfs_file_write(
            m_pFsHolder,
            m_pFileHandle.get(),
            dataHolder.data(),
            static_cast<lfs_size_t>(dataHolder.size()));
        co_return;
    }

    CoroUtils::Task<std::span<std::uint8_t>> read(std::span<std::uint8_t> outBuffer) noexcept
    {
        lfs_file_read(
            m_pFsHolder,
            m_pFileHandle.get(),
            outBuffer.data(),
            static_cast<lfs_size_t>(outBuffer.size()));
        co_return outBuffer;
    }

    lfs_file_t* nativeHandle(const FilesystemPasskey& passkey) noexcept
    {
        Meta::UnuseVar(passkey);
        return m_pFileHandle.get();
    }

private:
    std::unique_ptr<lfs_file_t> m_pFileHandle;
    lfs_t* m_pFsHolder;
};
} // namespace Platform::Fs
