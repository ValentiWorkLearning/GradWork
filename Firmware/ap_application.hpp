#pragma once

#include <logger/logger_service.hpp>

#include "graphics/gs_lvgl_service.hpp"

#include <sp_fake_services_creator.hpp>

#include <ih/sp_ibattery_service.hpp>
#include <ih/sp_idatetime_service.hpp>
#include <ih/sp_iheartrate_service.hpp>

#include <ih/drivers/ih_ible_softdevice.hpp>

#include <board/watchboard.hpp>

#include <utils/Noncopyable.hpp>

class Application : public Utils::noncopyable
{

public:
    Application() noexcept;

    ~Application() noexcept;

public:
    void runApplicationLoop() noexcept;

private:
    void initBoard() noexcept;

    void initServices() noexcept;

    void initPeripheral() noexcept;

    void initBleStack() noexcept;

    void initGraphicsStack() noexcept;

    void connectBoardSpecificEvents() noexcept;

private:
    Ble::Stack::TSoftDevicePtr m_bleStackKeeper;
    std::unique_ptr<ServiceProviders::IServiceCreator> m_fakeServiceProvider;
    std::unique_ptr<ServiceProviders::BatteryService::IBatteryLevelAppService>
        m_batteryLevelService;
    std::unique_ptr<ServiceProviders::HeartrateService::IHeartrateService> m_heartrateService;
    std::unique_ptr<ServiceProviders::DateTimeService::IDateTimeService> m_dateTimeService;
    std::unique_ptr<Graphics::LvglGraphicsService> m_graphicsService;
    WatchBoard::TBoardPtr m_pBoardImpl;
};
