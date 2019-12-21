#pragma once

#include "nrf_delay.h"
#include "nrf.h"
#include "boards.h"
#include "bsp.h"

#include "drivers/display/display_st7789v_constants.hpp"
#include "drivers/display/display_st7789v.hpp"

#include "drivers/spi/spi_wrapper.hpp"

#include "drivers/ble/ble_custom_service.hpp"
#include "drivers/ble/ble_softdevice.hpp"

#include "logger/logger_service.hpp"

#include "graphics/gs_lvgl_service.hpp"

#include "service_providers/ih/sp_ibattery_service.hpp"
#include "service_providers/sp_fake_services_creator.hpp"

#include "Noncopyable.hpp"

class Application
{

public:

    Application();

    ~Application() = default;

public:

    void runApplicationLoop();

    void runDisplayTest();

private:

    void initInterfaces();

    void initBoard();

    void initServices();

    void initPeripheral();

    void initBleStack();

    void initGraphicsStack();

private:

    std::unique_ptr<Interface::Spi::SpiBus> m_displaySpiInstance;
    std::unique_ptr<Ble::Stack::BleStackKeeper> m_bleStackKeeper;
    std::unique_ptr<ServiceProviders::IServiceCreator> m_fakeServiceProvider;
    std::unique_ptr<ServiceProviders::BatteryService::IBatteryLevelAppService> m_batteryLevelService;
    std::unique_ptr<Graphics::LvglGraphicsService> m_graphicsService;
};
