#pragma once

#include "ih_block_device.hpp"
#include <etl/vector.h>

#include <logger/logger_service.hpp>
#include <span>

namespace Filesystem::BlockDevice
{

template <typename TWrappee>
class LogAdaptorBlockDevice : public BlockDeviceEntity<LogAdaptorBlockDevice<TWrappee>>
{

public:
    constexpr std::uint32_t getBlockSize() const noexcept
    {
        return m_wrappedNode.getBlockSize();
    }
    constexpr std::uint32_t getBlocksCount() const noexcept
    {
        return m_wrappedNode.getBlocksCount();
    }
    constexpr std::uint32_t getReadSize() const noexcept
    {
        return m_wrappedNode.getReadSize();
    }
    constexpr std::uint32_t getProgSize() const noexcept
    {
        return m_wrappedNode.getProgSize();
    }
    constexpr std::uint32_t getEraseSize() const noexcept
    {
        return m_wrappedNode.getEraseSize();
    }

    CoroUtils::VoidTask write(
        std::uint32_t _address,
        const std::uint8_t* _blockData,
        std::uint32_t _blockSize) noexcept
    {
        LOG_DEBUG(fmt::format(
            "Block Device WRITE to address: {address} blockData: {span_data:f} ",
            fmt::arg("address", _address),
            fmt::arg("span_data", std::span(_blockData, _blockSize))));

        co_await m_wrappedNode.write(_address, _blockData, _blockSize);
    }
    CoroUtils::VoidTask read(
        std::uint8_t* _pBlockOut,
        std::uint32_t _address,
        std::uint32_t _blockSize) noexcept
    {
        co_await m_wrappedNode.read(_pBlockOut, _address, _blockSize);

        LOG_DEBUG(fmt::format(
            "Block Device READ from address: {address} blockData: {span_data:f} ",
            fmt::arg("address", _address),
            fmt::arg("span_data", std::span(static_cast<const uint8_t*>(_pBlockOut), _blockSize))));
    }

private:
    TWrappee m_wrappedNode;
};
} // namespace Filesystem::BlockDevice