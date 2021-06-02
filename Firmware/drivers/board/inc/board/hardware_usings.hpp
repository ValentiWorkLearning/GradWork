#pragma once

#include <ih/drivers/ih_button_driver.hpp>
#ifndef USE_DEVICE_SPECIFIC
#include <backends/spi_backend_desktop.hpp>
#include <buttons/bt_win32_hardware_buttons_manual_backend.hpp>
#else
#include <backends/spi_backend_nrf.hpp>
#include <buttons/bt_nordic_hardware_backend.hpp>
#endif

#include <spi/spi_wrapper_async_templated.hpp>
#include <windbondflash/winbond_flash_templated.hpp>

namespace Hal
{

#ifndef USE_DEVICE_SPECIFIC
using BoardTimer = Buttons::Win32TimerBackend;
using ButtonsBackend = Buttons::Win32ButtonsBackend;
using TFlashDriver = ExternalFlash::WinbondFlashDriver<
    Interface::SpiTemplated::SpiBus<Interface::SpiTemplated::SpiBusDesktopBackend>>;
#else
using BoardTimer = Buttons::NordicTimerBackend;
using ButtonsBackend = Buttons::NordicButtonsBackend;
using TFlashDriver = ExternalFlash::WinbondFlashDriver<Interface::SpiTemplated::SpiBus<
    Interface::SpiTemplated::NordicSpi<Interface::SpiTemplated::SpiInstance::M1>>>;
#endif

using ButtonsDriver = Buttons::ButtonsDriverTemplate<BoardTimer, ButtonsBackend>;
}; // namespace Hal