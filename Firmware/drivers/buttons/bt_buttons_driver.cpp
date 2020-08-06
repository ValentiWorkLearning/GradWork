#include "inc/buttons/bt_buttons_driver.hpp"


namespace Buttons
{

TButtonsDriverPtr createButtonsDriver()
{
    return std::make_unique<ButtonsDriver>();
}

ButtonsDriver::ButtonsDriver()
	:	m_timerImpl{nullptr}
	,	m_buttonBackendImpl{nullptr}
	,	m_buttons{}
	,	m_lastPressedId{ std::numeric_limits<std::uint8_t>::max() }
	,	m_pressCount{ std::numeric_limits<std::uint8_t>::max() }

{
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

			if ( m_lastPressedId != _buttonId )
			{
				m_lastPressedId = _buttonId;
				m_pressCount = 1;
				m_timerImpl->stopTimer();
				m_timerImpl->startTimer();
			}
			else
			{
				m_pressCount = m_pressCount < 2 ? m_pressCount + 1 : 1;
			}

		}
	}
	else if( _buttonEvent == ButtonBackendEvent::Released )
	{
		if( m_buttons[ _buttonId ].state == ButtonState::kButtonDown )
		{
			m_buttons[ _buttonId ].state = ButtonState::kButtonUp;

			onButtonEvent.emit( { _buttonId, ButtonState::kButtonUp } );

			const bool shoulEmitDoubleClickEvent =
							m_pressCount == 2
					&&		_buttonId == m_lastPressedId
					&&		!m_timerImpl->isTimerEllapsed();

			if ( shoulEmitDoubleClickEvent )
			{
				onButtonEvent.emit({ _buttonId, ButtonState::kButtonDblClick });
			}
			else {
				onButtonEvent.emit({ _buttonId, ButtonState::kButtonClick });
			}

		}

	}

}

} // Buttons