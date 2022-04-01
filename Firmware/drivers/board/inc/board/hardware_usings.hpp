#pragma once

#include <ih/drivers/ih_button_driver.hpp>
#ifndef USE_DEVICE_SPECIFIC
#include <backends/spi_backend_desktop.hpp>
#include <buttons/bt_firmware_simulator_hardware_buttons_manual_backend.hpp>
#include <filesystem/block_device_wrapper/adaptor_block_device.hpp>
#include <filesystem/block_device_wrapper/combiner_block_device.hpp>
#include <filesystem/block_device_wrapper/heap_block_device.hpp>
#else
#include <backends/spi_backend_nrf.hpp>
#include <buttons/bt_nordic_hardware_backend.hpp>
#include <filesystem/block_device_wrapper/adaptor_block_device.hpp>
#include <filesystem/block_device_wrapper/spi_block_device.hpp>
#endif

#include <spi/spi_wrapper_async_templated.hpp>
#include <windbondflash/winbond_flash_templated.hpp>

#include <filesystem/platform_filesystem.hpp>

namespace Hal
{

#ifndef USE_DEVICE_SPECIFIC
using BoardTimer = Buttons::FirmwareSimulatorTimerBackend;
using ButtonsBackend = Buttons::FirmwareSimulatorButtonsBackend;
using TFlashDriver = ExternalFlash::WinbondFlashDriver<
    Interface::SpiTemplated::SpiBus<Interface::SpiTemplated::SpiBusDesktopBackend>>;

using TLogHeapBlockDevice =
    Filesystem::BlockDevice::LogAdaptorBlockDevice<Filesystem::BlockDevice::HeapBlockDevice<
        Filesystem::BlockDevice::kBlockSize,
        Filesystem::BlockDevice::kSectorsCount,
        Filesystem::BlockDevice::kReadSize,
        Filesystem::BlockDevice::kEraseSize>>;

using TFilesystem = Platform::Fs::Holder<TLogHeapBlockDevice>;
#else
using BoardTimer = Buttons::NordicTimerBackend;
using ButtonsBackend = Buttons::NordicButtonsBackend;
using TFlashDriver = ExternalFlash::WinbondFlashDriver<
    Interface::SpiTemplated::SpiBus<Interface::SpiTemplated::NordicSpi<
        Interface::SpiTemplated::SpiInstance::M1,
        Interface::SpiTemplated::SpiInstance::ChipSelectDrivenByUser>>>;

struct BoardSpiFlashDescriptor
{
    static constexpr inline std::size_t kBlockSize = 256;
    static constexpr inline std::size_t kSectorsCount = 65'536;
    static constexpr inline std::size_t kReadSize = 256;
    static constexpr inline std::size_t kEraseSize = 4096;
};

using TSpiFlashBlockDevice = Filesystem::BlockDevice::LogAdaptorBlockDevice<
    Filesystem::BlockDevice::SpiFlashBlockDevice<TFlashDriver, BoardSpiFlashDescriptor>>;

using TFilesystem = Platform::Fs::Holder<TSpiFlashBlockDevice>;

#endif

using ButtonsDriver = Buttons::ButtonsDriverTemplate<BoardTimer, ButtonsBackend>;
}; // namespace Hal
