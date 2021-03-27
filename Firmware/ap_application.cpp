#include "ap_application.hpp"

#include "ih/drivers/ih_ible_softdevice.hpp"
#include "ih/drivers/ih_ble_service_factory.hpp"

#include "board/watchboard.hpp"
#include "i2c/i2c_test.hpp"

#include "graphics/gs_lvgl_service.hpp"
#include "graphics/ih/gs_imain_window.hpp"
#include "graphics/gs_event_dispatcher.hpp"

#include <utils/SimpleSignal.hpp>
#include <utils/CoroUtils.hpp>

#include <logger/logger_service.hpp>


#include <optional>

namespace EventConvert
{
    Graphics::Events::TButtonsEvents toButtonEvent( Buttons::ButtonState _buttonToConvert )
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
}

Application::Application()
{
    initBoard();
    initPeripheral();
    initServices();
    initGraphicsStack();
    //initBleStack();
    connectBoardSpecificEvents();
}

Application::~Application() = default;

void
Application::initBoard()
{
    m_pBoardImpl = WatchBoard::createBoard();
}

void
Application::initServices()
{
    m_fakeServiceProvider = ServiceProviders::getFakeServiceCreator();
    m_batteryLevelService = m_fakeServiceProvider->getBatteryService();
    m_heartrateService = m_fakeServiceProvider->getHeartrateService();
    m_dateTimeService = m_fakeServiceProvider->getDateTimeService();
}

void
Application::initPeripheral()
{

}

void
Application::initBleStack()
{

    m_bleStackKeeper = std::move(
            Ble::Stack::createSoftDevice(
                Ble::ServiceFactory::getBleServiceFactory()
            )
    );

    if( !m_bleStackKeeper )
        return;

    auto& batteryServiceBle = m_bleStackKeeper->getBatteryService();

    m_batteryLevelService->onBatteryLevelChangedSig.connect(
        [ &batteryServiceBle ]( std::uint8_t _newBatteryValue )
        {
                batteryServiceBle.onBatteryLevelChanged( _newBatteryValue );
        }
    );

    auto& pMainWindow = m_graphicsService->getMainWindow();
    m_bleStackKeeper->onConnected.connect(
        [&pMainWindow]
        {
            pMainWindow.getEventDispatcher().postEvent(
                {
                        Graphics::Events::EventGroup::BleDevice
                    ,   Graphics::Events::TBleClientEvents::DeviceConnected
                    ,   std::nullopt
                }
            );
        }
    );

    m_bleStackKeeper->onDisconnected.connect(
        [&pMainWindow]
        {
            pMainWindow.getEventDispatcher().postEvent(
                {
                        Graphics::Events::EventGroup::BleDevice
                    ,   Graphics::Events::TBleClientEvents::DeviceDisconnected
                    ,   std::nullopt
                }
            );
        }
    );

    auto& dateTimeService = m_bleStackKeeper->getDateTimeService();
    dateTimeService.onDateTimeDiscovered.connect(
        [&pMainWindow](const TimeWrapper& _newBleTime )
        {
            pMainWindow.getEventDispatcher().postEvent(
                {
                        Graphics::Events::EventGroup::DateTime
                    ,   Graphics::Events::TDateTimeEvents::DateTimeChanged
                    ,   _newBleTime
                }
            );
        }
    );
}

void
Application::initGraphicsStack()
{
    m_graphicsService = Graphics::createGraphicsService();

    auto& pMainWindow = m_graphicsService->getMainWindow();

    m_batteryLevelService->onBatteryLevelChangedSig.connect(
        [ &pMainWindow ]( std::uint8_t _newBatteryValue )
        {
            pMainWindow.getEventDispatcher().postEvent(
                {       Graphics::Events::EventGroup::Battery
                    ,   Graphics::Events::TBatteryEvents::BatteryLevelChanged
                    ,   _newBatteryValue
                }
            );
        }
    );

    m_dateTimeService->onDateTimeChanged.connect(
        [&pMainWindow]( const TimeWrapper& _newTime )
        {
            pMainWindow.getEventDispatcher().postEvent(
                {       Graphics::Events::EventGroup::DateTime
                    ,   Graphics::Events::TDateTimeEvents::DateTimeChanged
                    ,   _newTime
                }
            );
        }
    );
}


void
Application::connectBoardSpecificEvents()
{
    auto& pMainWindow = m_graphicsService->getMainWindow();

    m_pBoardImpl->getButtonsDriver()->onButtonEvent.connect(
        [&pMainWindow]( Buttons::ButtonEvent _buttonEvent )
        {
            Graphics::Events::HardwareButtonId graphicsButton{
                Graphics::Events::enumConvert<Graphics::Events::HardwareButtonId>(_buttonEvent.buttonId)
            };

            pMainWindow.getEventDispatcher().postEvent(
                {
                        Graphics::Events::EventGroup::Buttons
                    ,   EventConvert::toButtonEvent( _buttonEvent.buttonEvent )
                    ,   graphicsButton
                }
            );
        }
    );
}

void
Application::runApplicationLoop()
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
