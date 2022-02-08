#pragma once
#include <tuple>
#include <utils/CoroUtils.hpp>

namespace Filesystem::BlockDevice
{
template <typename... CombinedBlocks> class CombinerBlockDevice
{
public:
    using TCombinedBlocksStore = std::tuple<CombinedBlocks...>;

    constexpr std::uint32_t getBlockSize() const noexcept
    {
        return getFirstBlock()->getBlockSize();
    }
    constexpr std::uint32_t getBlocksCount() const noexcept
    {
        return getFirstBlock()->getBlocksCount();
    }
    constexpr std::uint32_t getReadSize() const noexcept
    {
        return getFirstBlock()->getReadSize();
    }
    constexpr std::uint32_t getProgSize() const noexcept
    {
        return getFirstBlock()->getProgSize();
    }
    constexpr std::uint32_t getEraseSize() const noexcept
    {
        return getFirstBlock()->getEraseSize();
    }

    CoroUtils::VoidTask write(
        std::uint32_t _address,
        const std::uint8_t* _blockData,
        std::uint32_t _blockSize) noexcept
    {
        co_await launchAllWrite(
            _address,
            _blockData,
            _blockSize,
            std::make_integer_sequence<std::size_t, sizeof...(CombinedBlocks)>{});
    }

    CoroUtils::VoidTask read(
        std::uint8_t* _pBlockOut,
        std::uint32_t _address,
        std::uint32_t _blockSize) noexcept
    {
        // TODO add comarison of the differrent block device reads
        co_await getFirstBlock()->read(_pBlockOut, _address, _blockSize);
    }

private:
    template <std::size_t... Indexes>
    CoroUtils::VoidTask launchAllWrite(
        std::uint32_t _address,
        const std::uint8_t* _blockData,
        std::uint32_t _blockSize,
        std::integer_sequence<std::size_t, Indexes...>) noexcept
    {
        (co_await std::get<Indexes>(m_combinedBlocks).write(_address, _blockData, _blockSize), ...);
    }

    decltype(auto) getFirstBlock() noexcept
    {
        return &std::get<0>(m_combinedBlocks);
    }

    decltype(auto) getFirstBlock() const noexcept
    {
        return &std::get<0>(m_combinedBlocks);
    }

private:
    TCombinedBlocksStore m_combinedBlocks;
};

} // namespace Filesystem::BlockDevice