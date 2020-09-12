#include "ih/drivers/ih_display_driver_creator.hpp"

#include "display/display_st7789v.hpp"
#include "display/display_gc9a01.hpp"
#include "spi/spi_wrapper.hpp"

namespace DisplayCreator
{
std::unique_ptr<DisplayDriver::IDisplayDriver> createDisplayDriver()
{
#if defined USE_ST7789V_BACKEND
    return DisplayDriver::createDisplayDriverSt7789V(
                Interface::Spi::SpiBus(
                    Interface::Spi::SpiInstance::fillSpiDescriptor(
                        Interface::Spi::SpiInstance::TSpiDescriptor::M2
                    )
                )
            ,   DisplayDriver::St7789v::Disp240_320::Width
            ,   DisplayDriver::St7789v::Disp240_320::Height
        );
#elif defined USE_GC9A01_BACKEND
    return DisplayDriver::createDisplayDriverGC9A01(
                Interface::Spi::SpiBus(
                    Interface::Spi::SpiInstance::fillSpiDescriptor(
                        Interface::Spi::SpiInstance::TSpiDescriptor::M2
                    )
                )
            ,   DisplayDriver::St7789v::Disp240_320::Width
            ,   DisplayDriver::St7789v::Disp240_320::Height
        );
#endif
    return nullptr;
}
};