#include "ih/drivers/ih_display_driver_creator.hpp"

#include "display/display_st7789v.hpp"
#include "spi/spi_wrapper.hpp"

namespace DisplayCreator
{
std::unique_ptr<DisplayDriver::IDisplayDriver> createDisplayDriver()
{
#if defined USE_ST7789V_BACKEND
    return DisplayDriver::createDisplayDriver(
                Interface::Spi::createSpiBus<Interface::Spi::SpiInstance::M2>()
            ,   DisplayDriver::St7789v::Disp240_320::Width
            ,   DisplayDriver::St7789v::Disp240_320::Height
        );
#endif
    return nullptr;
}
};