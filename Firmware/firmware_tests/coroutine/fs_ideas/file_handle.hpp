
#include "filesystem_holder.hpp"
#include "fs_common.hpp"
#include <cstdint>
#include <lfs.h>
#include <span>
#include <string>
#include <utils/CoroUtils.hpp>
#include <utils/MetaUtils.hpp>

namespace Platform::Fs
{
class File
{
public:
    explicit File() = default;
    explicit File(lfs_file_t fileHandle, Platform::Fs::Holder* pFsHolder)
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
    Platform::Fs::Holder* m_pFsHolder;
};

} // namespace Platform::Fs