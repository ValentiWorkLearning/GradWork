#pragma once

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

#include "ih/drivers/ih_button_driver.hpp"

#include <memory>

namespace WatchBoard
{

class Board
{

public:

	void initBoard();

	void toggleStatusLed();

	Buttons::IButtonsDriver* getButtonsDriver();

	Buttons::IButtonsDriver* getButtonsDriver() const;

private:

	Buttons::TButtonsDriverPtr m_pButtonsDriver;
	Buttons::TButtonTimerWrapperPtr m_pButtonsTimer;
	Buttons::TButtonsBackendPtr m_pButtonsBackend;
};

using TBoardPtr = std::unique_ptr<Board>;
TBoardPtr createBoard();

} // namespace WatchBoard
