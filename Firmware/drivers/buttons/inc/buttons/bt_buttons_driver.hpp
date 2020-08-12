#pragma once

#include "ih/drivers/ih_button_driver.hpp"

#include "utils/FastPimpl.hpp"
#include "utils/Platform.hpp"

namespace Buttons
{

class ButtonsDriver
	:	public IButtonsDriver
{

public:

	ButtonsDriver();

	void setTimer(IButtonTimerWrapper* _pTimerWrapper)override;

	void setButtonsBackend(IButtonsBackend* _pTimerWrapper)override;

private:

	void handleTimerExpired();

	void handleButtonsBackendEvent( ButtonId _buttonId, ButtonBackendEvent _buttonEvent );

private:
	struct ButtonDescriptor
	{
		ButtonId id;
		ButtonState state;
	};

	static constexpr std::uint8_t ButtonsCount = 5;
	using ButtonsCollection = std::array<ButtonDescriptor, ButtonsCount>;

	IButtonTimerWrapper* m_timerImpl;
	IButtonsBackend* m_buttonBackendImpl;
	ButtonsCollection m_buttons;

	ButtonId m_lastPressedId;
	std::uint8_t m_pressCount;
};

TButtonsDriverPtr createButtonsDriver();

} // Buttons
