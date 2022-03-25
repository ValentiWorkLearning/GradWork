#include "ap_application.hpp"

#include "ih/drivers/ih_ble_service_factory.hpp"
#include "ih/drivers/ih_ible_softdevice.hpp"

#include "board/watchboard.hpp"
#include "i2c/i2c_test.hpp"

#include "graphics/gs_event_dispatcher.hpp"
#include "graphics/gs_lvgl_service.hpp"
#include "graphics/ih/gs_imain_window.hpp"

#include <utils/CoroUtils.hpp>
#include <utils/SimpleSignal.hpp>

#include <logger/logger_service.hpp>

#include <optional>

namespace GsEvents = Graphics::Events;

namespace EventConvert
{
Graphics::Events::TButtonsEvents toButtonEvent(Buttons::ButtonState _buttonToConvert)
{
    switch (_buttonToConvert)
    {
    case Buttons::ButtonState::kButtonUp:
        return Graphics::Events::TButtonsEvents::ButtonReleased;
    case Buttons::ButtonState::kButtonDown:
        return Graphics::Events::TButtonsEvents::ButtonPressed;
    case Buttons::ButtonState::kButtonClick:
        return Graphics::Events::TButtonsEvents::ButtonClicked;
    case Buttons::ButtonState::kButtonDblClick:
        return Graphics::Events::TButtonsEvents::ButtonDblClick;
    case Buttons::ButtonState::kButtonLongPress:
        return Graphics::Events::TButtonsEvents::ButtonLongClick;
    default:
        assert(false);
        return Graphics::Events::TButtonsEvents::ButtonPressed;
    }
}
} // namespace EventConvert

Application::Application() noexcept
{
    initBoard();
    initPeripheral();
    initServices();
    initGraphicsStack();
    initBleStack();
    connectBoardSpecificEvents();
}

Application::~Application() noexcept = default;

void Application::initBoard() noexcept
{
    m_pBoardImpl = WatchBoard::createBoard();
}

void Application::initServices() noexcept
{
    auto bleServiceProvider = ServiceProviders::getFakeServiceCreator();
    m_batteryLevelService = bleServiceProvider->getBatteryService();
    m_heartrateService = bleServiceProvider->getHeartrateService();
    m_dateTimeService = bleServiceProvider->getDateTimeService();
}

void Application::initPeripheral() noexcept
{
}

Application& Application::Instance()
{
    static Application app;
    return app;
}

void Application::initBleStack() noexcept
{

    m_bleStackKeeper =
        std::move(Ble::Stack::createSoftDevice(Ble::ServiceFactory::getBleServiceFactory()));

    if (!m_bleStackKeeper)
        return;

    auto& batteryServiceBle = m_bleStackKeeper->getBatteryService();

    m_batteryLevelService->onBatteryLevelChangedSig.connect(
        [&batteryServiceBle](std::uint8_t _newBatteryValue) {
            batteryServiceBle.onBatteryLevelChanged(_newBatteryValue);
        });

    auto& pMainWindow = m_graphicsService->getMainWindow();
    m_bleStackKeeper->onConnected.connect([&pMainWindow] {
        pMainWindow.getEventDispatcher().postEvent(
            {GsEvents::EventGroup::BleDevice,
             GsEvents::to_underlying(GsEvents::TBleClientEvents::DeviceConnected),
             std::nullopt});
    });

    m_bleStackKeeper->onDisconnected.connect([&pMainWindow] {
        pMainWindow.getEventDispatcher().postEvent(
            {GsEvents::EventGroup::BleDevice,
             GsEvents::to_underlying(GsEvents::TBleClientEvents::DeviceDisconnected),
             std::nullopt});
    });

    auto& dateTimeService = m_bleStackKeeper->getDateTimeService();
    dateTimeService.onDateTimeDiscovered.connect([&pMainWindow](const TimeWrapper& _newBleTime) {
        pMainWindow.getEventDispatcher().postEvent(
            {GsEvents::EventGroup::DateTime,
             GsEvents::to_underlying(GsEvents::TDateTimeEvents::DateTimeChanged),
             _newBleTime});
    });
}

void Application::initGraphicsStack() noexcept
{
    m_graphicsService = Graphics::createGraphicsService();

    auto& pMainWindow = m_graphicsService->getMainWindow();

    m_batteryLevelService->onBatteryLevelChangedSig.connect(
        [&pMainWindow](std::uint8_t _newBatteryValue) {
            pMainWindow.getEventDispatcher().postEvent(
                {GsEvents::EventGroup::Battery,
                 GsEvents::to_underlying(GsEvents::TBatteryEvents::BatteryLevelChanged),
                 _newBatteryValue});
        });

    m_dateTimeService->onDateTimeChanged.connect([&pMainWindow](const TimeWrapper& _newTime) {
        pMainWindow.getEventDispatcher().postEvent(
            {GsEvents::EventGroup::DateTime,
             GsEvents::to_underlying(GsEvents::TDateTimeEvents::DateTimeChanged),
             _newTime});
    });
}

void Application::connectBoardSpecificEvents() noexcept
{
    auto& pMainWindow = m_graphicsService->getMainWindow();

    m_pBoardImpl->getButtonsDriver()->onButtonEvent.connect([&pMainWindow](
                                                                Buttons::ButtonEvent _buttonEvent) {
        GsEvents::HardwareButtonId graphicsButton{GsEvents::to_underlying(_buttonEvent.buttonId)};

        pMainWindow.getEventDispatcher().postEvent(
            {GsEvents::EventGroup::Buttons,
             GsEvents::to_underlying(EventConvert::toButtonEvent(_buttonEvent.buttonEvent)),
             graphicsButton});
    });
}

void Application::runApplicationLoop() noexcept
{
    I2C::scanI2CSensors();

    m_batteryLevelService->startBatteryMeasure();
    m_dateTimeService->launchService();
    m_pBoardImpl->ledToggle();

    while (true)
    {
        CoroUtils::CoroQueueMainLoop::GetInstance().processQueue();
        Simple::Lib::ExecuteLaterPool::Instance().processQueue();
        m_graphicsService->executeGlTask();
    }
}
