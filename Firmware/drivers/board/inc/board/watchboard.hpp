#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

#include "hardware_usings.hpp"
#include <memory>

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

    TFlashDriverPtr m_pFlashDriver;
};

using TBoardPtr = std::unique_ptr<Board>;
TBoardPtr createBoard() noexcept;

} // namespace WatchBoard
