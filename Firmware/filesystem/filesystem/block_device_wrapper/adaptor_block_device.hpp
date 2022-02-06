#pragma once

#include "ih_block_device.hpp"
#include <etl/vector.h>

#include <spdlog/spdlog.h>
#include <span>

template <> struct fmt::formatter<std::span<const std::uint8_t>>
{

    constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin())
    {

        auto it = ctx.begin(), end = ctx.end();

        if (it != end && *it == 'f')
        {
            ++it;
            if (it != end && *it != '}')
                throw format_error("invalid format");
        }
        return it;
    }

    template <typename FormatContext>
    auto format(const std::span<const std::uint8_t>& p, FormatContext& ctx) -> decltype(ctx.out())
    {

        auto tempFormatHolder = std::string_view{
            reinterpret_cast<const char*>(p.data()),
            reinterpret_cast<const char*>(p.data()) + p.size()};
        auto dataSize = tempFormatHolder.length();

        return format_to(ctx.out(), "{}", tempFormatHolder);
    }
};

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
        spdlog::info(
            "Block Device WRITE to address: {address} blockData: {span_data:f} ",
            fmt::arg("address", _address),
            fmt::arg("span_data", std::span(_blockData, _blockSize)));

        co_await m_wrappedNode.write(_address, _blockData, _blockSize);
    }
    CoroUtils::VoidTask read(
        std::uint8_t* _pBlockOut,
        std::uint32_t _address,
        std::uint32_t _blockSize) noexcept
    {
        co_await m_wrappedNode.read(_pBlockOut, _address, _blockSize);

        spdlog::info(
            "Block Device READ from address: {address} blockData: {span_data:f} ",
            fmt::arg("address", _address),
            fmt::arg("span_data", std::span(static_cast<const uint8_t*>(_pBlockOut), _blockSize)));
    }

private:
    TWrappee m_wrappedNode;
};
} // namespace Wrapper