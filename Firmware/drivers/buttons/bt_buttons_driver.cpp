#include "inc/buttons/bt_buttons_driver.hpp"


namespace Buttons
{

TButtonsDriverPtr createButtonsDriver()
{
    return std::make_unique<ButtonsDriver>();
}

void ButtonsDriver::setTimer(IButtonTimerWrapper* _pTimerWrapper)
{
	m_timerImpl = _pTimerWrapper;
	m_timerImpl->onTimerExpired.connect(
		[this]
		{
			handleTimerExpired();
		}
	);
}
void ButtonsDriver::setButtonsBackend(IButtonsBackend* _pTimerWrapper)
{
	m_buttonBackendImpl = _pTimerWrapper;
	m_buttonBackendImpl->onButtonEvent.connect(
		[this](std::uint8_t _buttonId, ButtonBackendEvent _buttonEvent)
		{
			handleButtonsBackendEvent(_buttonId, _buttonEvent);
		}
	);
}

void ButtonsDriver::handleTimerExpired()
{
}

void ButtonsDriver::handleButtonsBackendEvent( std::uint8_t _buttonId, ButtonBackendEvent _buttonEvent )
{
	if( _buttonEvent == ButtonBackendEvent::Pressed )
	{
		if( m_buttons[ _buttonId ].state == ButtonState::kButtonUp )
		{
			m_buttons[ _buttonId ].state = ButtonState::kButtonDown;
			onButtonEvent.emit({ _buttonId, ButtonState::kButtonDown });
		}
	}
	else if( _buttonEvent == ButtonBackendEvent::Released )
	{
		if( m_buttons[ _buttonId ].state == ButtonState::kButtonDown )
		{
			m_buttons[ _buttonId ].state = ButtonState::kButtonUp;

			onButtonEvent.emit( { _buttonId, ButtonState::kButtonUp } );
			onButtonEvent.emit( { _buttonId, ButtonState::kButtonClick } );
		}
	}

}

} // Buttons