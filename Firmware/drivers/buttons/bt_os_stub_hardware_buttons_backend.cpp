#include "inc/buttons/bt_os_hardware_buttons_manual_backend.hpp"

#include "utils/CallbackConnector.hpp"
#include "utils/MetaUtils.hpp"

namespace Buttons
{

OsTimerBackend::OsTimerBackend() : m_isTimerEllapsed{true}
{
}

void OsTimerBackend::startTimer()
{
}

void OsTimerBackend::stopTimer()
{
}

void OsTimerBackend::initialize()
{
}

bool OsTimerBackend::isTimerEllapsed() const
{
    return m_isTimerEllapsed;
}

OsButtonsBackend::OsButtonsBackend()
{
}

void OsButtonsBackend::initialize()
{
}

} // namespace Buttons
