#include "ap_application.hpp"

#include "logger_service.hpp"
#include "graphics/gs_lvgl_service.hpp"

Application::Application()
{
    initBoard();
    initInterfaces();
    initPeripheral();
    initServices();
    initGraphicsStack();
    initBleStack();
}

void
Application::initInterfaces()
{
    m_displaySpiInstance = Interface::Spi::createSpiBus<Interface::Spi::SpiInstance::M0>();
}

void
Application::initBoard()
{
    /* Configure board. */
    bsp_board_init( BSP_INIT_LEDS );

    Logger::Instance().logDebugEndl( "Hello from E73 Mod Board!" );

    ret_code_t errorCode{};

    errorCode = app_timer_init();
    APP_ERROR_CHECK( errorCode );
}

void
Application::initServices()
{
    m_fakeServiceProvider = ServiceProviders::getFakeServiceCreator();
    m_batteryLevelService = m_fakeServiceProvider->getBatteryService();
}

void
Application::initPeripheral()
{
}

void
Application::initBleStack()
{
    m_bleStackKeeper = Ble::Stack::createBleStackKeeper();

    auto& batteryServiceBle = m_bleStackKeeper->getBatteryService();

    m_batteryLevelService->onBatteryLevelChangedSig.connect(
        [ &batteryServiceBle ]( std::uint8_t _newBatteryValue )
        {
                batteryServiceBle.onBatteryLevelChanged( _newBatteryValue );
        }
    );
}

void
Application::initGraphicsStack()
{
    m_graphicsService =  Graphics::createGraphicsService(
        DisplayDriver::createDisplayDriver(
                m_displaySpiInstance.get()
            ,   DisplayDriver::St7789v::Disp208_240::Width
            ,   DisplayDriver::St7789v::Disp208_240::Height
        )
    );
    nrf_delay_ms( 100 );
    m_graphicsService->runTest();
}

void
Application::runApplicationLoop()
{
    /* Toggle LEDs. */
    Logger::Instance().logDebugEndl( "Led toggle..." );
    auto ledToggler =
    []( size_t _delayTime )
    {
        bsp_board_led_invert(0);
        nrf_delay_ms( _delayTime );
    };

    while (true)
    {
        ledToggler( 300 );
        m_graphicsService->executeGlTask();
    }
}
