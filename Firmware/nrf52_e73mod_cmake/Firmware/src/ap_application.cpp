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
Application::runDisplayTest()
{
//    m_displayDriver->fillColor( DisplayDriver::Colors::BLACK );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::WHITE );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::RED );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::GREEN );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::BLUE );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::CYAN );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::MAGENTA );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::YELLOW );
//    nrf_delay_ms(120);
//    m_displayDriver->fillColor( DisplayDriver::Colors::ORANGE );
//    nrf_delay_ms(120);
//    m_displayDriver->fillRectangle( 40,40,20,20,DisplayDriver::Colors::BLACK );
//    nrf_delay_ms(120);

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
    }
}
