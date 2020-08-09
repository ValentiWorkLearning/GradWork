#pragma once

#include "ih/drivers/ih_button_driver.hpp"


namespace Buttons
{

TButtonsBackendPtr createButtonsBackend();

TButtonTimerWrapperPtr createTimerBackend();

}