#pragma once

#include "ih/drivers/ih_iexternal_flash.hpp"


namespace ExternalFlash
{

ExternalFlash::TFlashDevicePtr
createExternalFlashDriver();

} // namespace ExternalFlash