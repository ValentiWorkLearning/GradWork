#pragma once

#include "ih/drivers/ih_button_driver.hpp"

#include <atomic>

namespace Buttons
{

<<<<<<< HEAD:Firmware/drivers/buttons/inc/buttons/bt_os_hardware_buttons_manual_backend.hpp
class OsTimerBackend
{

public:
    OsTimerBackend();
=======
class FirmwareSimulatorTimerBackend
{

public:
    FirmwareSimulatorTimerBackend();
>>>>>>> master:Firmware/drivers/buttons/inc/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.hpp

public:
    Simple::Signal<void()> onTimerExpired;

public:
    bool isTimerEllapsed() const;

    void startTimer();

    void stopTimer();

    void initialize();

private:
    static constexpr inline std::uint32_t ClicksDetectionPeriodMs = 400;
    static constexpr inline std::uint32_t TimerId = 128;
    std::atomic<bool> m_isTimerEllapsed = false;
};

<<<<<<< HEAD:Firmware/drivers/buttons/inc/buttons/bt_os_hardware_buttons_manual_backend.hpp
class OsButtonsBackend
{

public:
    OsButtonsBackend();
=======
class FirmwareSimulatorButtonsBackend
{

public:
    FirmwareSimulatorButtonsBackend();
>>>>>>> master:Firmware/drivers/buttons/inc/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.hpp

public:
    Simple::Signal<void(ButtonId, ButtonBackendEvent)> onButtonEvent;

public:
    void initialize();
<<<<<<< HEAD:Firmware/drivers/buttons/inc/buttons/bt_os_hardware_buttons_manual_backend.hpp
=======

private:
    void initInternals();
>>>>>>> master:Firmware/drivers/buttons/inc/buttons/bt_firmware_simulator_hardware_buttons_manual_backend.hpp
};

} // namespace Buttons
