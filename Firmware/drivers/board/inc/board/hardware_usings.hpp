#pragma once

#include <ih/drivers/ih_button_driver.hpp>
#ifndef USE_DEVICE_SPECIFIC
#include <buttons/bt_win32_hardware_buttons_manual_backend.hpp>
#else
#include <buttons/bt_nordic_hardware_backend.hpp>
#endif

namespace Hal
{

#ifndef USE_DEVICE_SPECIFIC
	using BoardTimer = Buttons::Win32TimerBackend;
	using ButtonsBackend = Buttons::Win32ButtonsBackend;
#else
	using BoardTimer = Buttons::NordicTimerBackend;
	using ButtonsBackend = Buttons::NordicButtonsBackend;
#endif


	using ButtonsDriver = Buttons::ButtonsDriverTemplate<BoardTimer, ButtonsBackend>;
};