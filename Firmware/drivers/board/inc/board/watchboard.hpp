#pragma once

#include <utils/FastPimpl.hpp>
#include <utils/Platform.hpp>

#include <memory>

#include <board/hardware_usings.hpp>
#include <filesystem/block_device_wrapper/spi_block_device.hpp>
#include <filesystem/platform_filesystem.hpp>

namespace WatchBoard
{

class Board : private Utils::noncopyable
{

public:
    Board() noexcept;

public:
    void ledToggle() noexcept;

    Hal::ButtonsDriver* getButtonsDriver() noexcept;

private:
    void initBoard() noexcept;

    void initBoardTimer() noexcept;

    void initBoardSpiFlash() noexcept;

    std::uint32_t convertToTimerTicks(std::chrono::milliseconds _interval) noexcept;

private:
    const std::chrono::milliseconds LedToggleTimeout = std::chrono::milliseconds{300};

private:
    Hal::ButtonsDriver m_buttonsDriver;
    using TFlashDriverPtr = std::unique_ptr<Hal::TFlashDriver>;
    using TFilesystemPtr = std::unique_ptr<Hal::TFilesystem>;

    TFilesystemPtr m_filesystem;
    TFlashDriverPtr m_pFlashDriver;
};

using TBoardPtr = std::unique_ptr<Board>;
TBoardPtr createBoard() noexcept;

} // namespace WatchBoard
