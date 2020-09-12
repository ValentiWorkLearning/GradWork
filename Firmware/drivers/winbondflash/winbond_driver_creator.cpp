#include "inc/windbondflash/winbond_driver_creator.hpp"

#if defined (USE_DEVICE_SPECIFIC)
#include "inc/windbondflash/winbond_flash.hpp"
#include "spi/spi_wrapper.hpp"
#else

#endif

namespace ExternalFlash
{

ExternalFlash::TFlashDevicePtr
createExternalFlashDriver()
{
#if defined (USE_DEVICE_SPECIFIC)
    return std::make_unique<WinbondFlash>(
        Interface::Spi::SpiBus(
            Interface::Spi::SpiInstance::fillSpiDescriptor(
                Interface::Spi::SpiInstance::TSpiDescriptor::M1
            )
        )
    );
#else
    return nullptr;
#endif
}

} // namespace ExternalFlash
