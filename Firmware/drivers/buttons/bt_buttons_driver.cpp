#include "inc/buttons/bt_buttons_driver.hpp"

#include "logger/logger_service.hpp"

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
		[this](ButtonId _buttonId, ButtonBackendEvent _buttonEvent)
		{
			handleButtonsBackendEvent(_buttonId, _buttonEvent);
		}
	);
}

void ButtonsDriver::handleTimerExpired()
{
}

void ButtonsDriver::handleButtonsBackendEvent( ButtonId _buttonId, ButtonBackendEvent _buttonEvent )
{
	using TButtonUnderlying = std::underlying_type_t<ButtonId>;
	auto arrayIndex = static_cast<TButtonUnderlying>( _buttonId );

	if( _buttonEvent == ButtonBackendEvent::kPressed )
	{
		if( m_buttons[ arrayIndex ].state == ButtonState::kButtonUp )
		{
			m_buttons[ arrayIndex ].state = ButtonState::kButtonDown;
			onButtonEvent.emit({ _buttonId, ButtonState::kButtonDown });

			if ( m_lastPressedId != _buttonId)
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
	else if( _buttonEvent == ButtonBackendEvent::kReleased )
	{
		if( m_buttons[ arrayIndex ].state == ButtonState::kButtonDown )
		{
			m_buttons[arrayIndex].state = ButtonState::kButtonUp;
			onButtonEvent.emit( { _buttonId, ButtonState::kButtonUp } );

			const bool shoulEmitDoubleClickEvent =
							m_pressCount == 2
					&&		_buttonId == m_lastPressedId
					&&		!m_timerImpl->isTimerEllapsed();

			if ( shoulEmitDoubleClickEvent )
			{
				onButtonEvent.emit({ _buttonId, ButtonState::kButtonDblClick });
				Logger::Instance().logDebugEndl("onButtonEvent.emit({ _buttonId, ButtonState::kButtonDblClick });");
				m_pressCount = 0;
			}
			else
			{
				if ( m_timerImpl->isTimerEllapsed() && _buttonId == m_lastPressedId && m_pressCount == 1 )
				{
					Logger::Instance().logDebugEndl("onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonLongPress });");
					onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonLongPress });
					m_pressCount = 0;
				}
				else
				{
					Logger::Instance().logDebugEndl("onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonClick });");
					onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonClick });
				}
			}
		}

	}

}

} // Buttons