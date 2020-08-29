#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

#include "ih/drivers/ih_button_driver.hpp"

#include <memory>

namespace WatchBoard
{

class Board
	:	private Utils::noncopyable
{

public:

	Board();

public:

	void enableLedToggle();

	Buttons::IButtonsDriver* getButtonsDriver();

	Buttons::IButtonsDriver* getButtonsDriver() const;

private:

	void initBoard();

	void initBoardTimer();

	std::uint32_t convertToTimerTicks( std::chrono::milliseconds _interval );

private:
    const std::chrono::milliseconds LedToggleTimeout = std::chrono::milliseconds{300};
private:

	Buttons::TButtonsDriverPtr m_pButtonsDriver;
	Buttons::TButtonTimerWrapperPtr m_pButtonsTimer;
	Buttons::TButtonsBackendPtr m_pButtonsBackend;
};

using TBoardPtr = std::unique_ptr<Board>;
TBoardPtr createBoard();

} // namespace WatchBoard
