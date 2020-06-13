#pragma once

#include "ih_display_idisplay.hpp"

namespace DisplayCreator
{
    std::unique_ptr<DisplayDriver::IDisplayDriver> createDisplayDriver();
}