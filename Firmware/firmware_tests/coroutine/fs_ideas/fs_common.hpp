#pragma once
namespace Platform::Fs
{
class File;
class Holder;

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

} // namespace Platform::Fs