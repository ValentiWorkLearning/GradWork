#pragma once

#include "logger/logger_service.hpp"

#include "graphics/gs_lvgl_service.hpp"

#include "service_providers/sp_fake_services_creator.hpp"

#include "service_providers/ih/sp_ibattery_service.hpp"
#include "service_providers/ih/sp_iheartrate_service.hpp"
#include "service_providers/ih/sp_idatetime_service.hpp"

#include "Noncopyable.hpp"

#if defined (USE_BLE_SERVICES)
namespace Ble::Stack
{
    class BleStackKeeper;
}
#endif

class Application
{

public:

    Application();

    ~Application();

public:

    void runApplicationLoop();

private:

    void initInterfaces();

    void initBoard();

    void initServices();

    void initPeripheral();

    void initBleStack();

    void initGraphicsStack();

    void runTwiTest();

private:

#if defined (USE_BLE_SERVICES)
    std::unique_ptr<Ble::Stack::BleStackKeeper> m_bleStackKeeper;
#endif

    std::unique_ptr<ServiceProviders::IServiceCreator> m_fakeServiceProvider;
    std::unique_ptr<ServiceProviders::BatteryService::IBatteryLevelAppService> m_batteryLevelService;
    std::unique_ptr<ServiceProviders::HeartrateService::IHeartrateService> m_heartrateService;
    std::unique_ptr<ServiceProviders::DateTimeService::IDateTimeService> m_dateTimeService;
    std::unique_ptr<Graphics::LvglGraphicsService> m_graphicsService;
};
