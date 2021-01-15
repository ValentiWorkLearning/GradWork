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

	Board();

public:

	void ledToggle();

	Hal::ButtonsDriver* getButtonsDriver();

private:

	void initBoard();

	void initBoardTimer();

	void initBoardSpiFlash();

	std::uint32_t convertToTimerTicks( std::chrono::milliseconds _interval );

private:
    const std::chrono::milliseconds LedToggleTimeout = std::chrono::milliseconds{300};
private:

	Hal::ButtonsDriver m_buttonsDriver;
	ExternalFlash::TFlashDevicePtr m_pFlashDriver;
};

using TBoardPtr = std::unique_ptr<Board>;
TBoardPtr createBoard();

} // namespace WatchBoard
