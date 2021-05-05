#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

#include "ih/drivers/ih_iexternal_flash.hpp"
#include "hardware_usings.hpp"

#include <memory>

namespace WatchBoard
{

class Board
	:	private Utils::noncopyable
{

public:

	Board()noexcept;

public:

	void ledToggle()noexcept;

	Hal::ButtonsDriver* getButtonsDriver()noexcept;

private:

	void initBoard()noexcept;

	void initBoardTimer()noexcept;

	void initBoardSpiFlash()noexcept;

	std::uint32_t convertToTimerTicks( std::chrono::milliseconds _interval )noexcept;

private:
    const std::chrono::milliseconds LedToggleTimeout = std::chrono::milliseconds{300};
private:

	Hal::ButtonsDriver m_buttonsDriver;
	ExternalFlash::TFlashDevicePtr m_pFlashDriver;
};

using TBoardPtr = std::unique_ptr<Board>;
TBoardPtr createBoard()noexcept;

} // namespace WatchBoard
