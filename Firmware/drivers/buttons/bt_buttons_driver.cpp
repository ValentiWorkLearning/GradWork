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
	,	m_buttons{
			ButtonDescriptor{ ButtonId::kLeftButtonTop, ButtonState::Undefined, 0, false }
		,	ButtonDescriptor{ ButtonId::kLeftButtonMedium, ButtonState::Undefined, 0, false }
		,	ButtonDescriptor{ ButtonId::kLeftButtonBottom, ButtonState::Undefined, 0, false }
		,	ButtonDescriptor{ ButtonId::kRightButtonTop, ButtonState::Undefined, 0, false }
		,	ButtonDescriptor{ ButtonId::kRightButtonBottom, ButtonState::Undefined, 0, false }
	}
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
	for( auto& buttonDescriptor : m_buttons )
	{
		if( buttonDescriptor.state != ButtonState::kButtonDown )
		{
			switch (buttonDescriptor.pressCount)
			{
			case 1:
				Logger::Instance().logDebugEndl("onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonClick });");
				onButtonEvent.emit( { buttonDescriptor.id, ButtonState::kButtonClick } );
			break;
			case 2:
				Logger::Instance().logDebugEndl("onButtonEvent.emit({ _buttonId, ButtonState::kButtonDblClick });");
				onButtonEvent.emit({ buttonDescriptor.id, ButtonState::kButtonDblClick });
			break;

			default:
				break;
			}
			Logger::Instance().logDebugEndl("EXPIRED HANDLE");
			buttonDescriptor.pressCount = 0;
		}
		else {
			buttonDescriptor.longPressTimeoutExpired = true;
		}
	}
}

void ButtonsDriver::handleButtonsBackendEvent( ButtonId _buttonId, ButtonBackendEvent _buttonEvent )
{
	using TButtonUnderlying = std::underlying_type_t<ButtonId>;
	auto arrayIndex = static_cast<TButtonUnderlying>( _buttonId );

	if( _buttonEvent == ButtonBackendEvent::kPressed )
	{
		m_buttons[ arrayIndex ].state = ButtonState::kButtonDown;
		onButtonEvent.emit({ _buttonId, ButtonState::kButtonDown });

		m_buttons[ arrayIndex ].pressCount = m_buttons[arrayIndex].pressCount + 1;

		if ( m_timerImpl->isTimerEllapsed() )
			m_timerImpl->startTimer();
	}
	else if( _buttonEvent == ButtonBackendEvent::kReleased )
	{
		m_buttons[arrayIndex].state = ButtonState::kButtonUp;
		onButtonEvent.emit( { _buttonId, ButtonState::kButtonUp } );

		if ( m_buttons[arrayIndex].longPressTimeoutExpired )
		{
			m_buttons[arrayIndex].pressCount = 0;
			m_buttons[arrayIndex].longPressTimeoutExpired = false;
			Logger::Instance().logDebugEndl("onButtonEvent.emit({ m_lastPressedId, ButtonState::kButtonLongPress });");
			onButtonEvent.emit({ m_buttons[arrayIndex].id, ButtonState::kButtonLongPress });
		}
	}

}

} // Buttons