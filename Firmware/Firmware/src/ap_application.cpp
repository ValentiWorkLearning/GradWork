#include "ap_application.hpp"

#include "logger_service.hpp"
#include "graphics/gs_lvgl_service.hpp"

#include "nrf_drv_twi.h"

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
    m_displaySpiInstance = Interface::Spi::createSpiBus<Interface::Spi::SpiInstance::M2>();
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
    m_heartrateService = m_fakeServiceProvider->getHeartrateService();
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
Application::runTwiTest()
{
    static const nrf_drv_twi_t m_twiHeartrate = NRF_DRV_TWI_INSTANCE(0);
    static const nrf_drv_twi_t m_twiMpu = NRF_DRV_TWI_INSTANCE(1);

    ret_code_t errorCode{};

    const nrf_drv_twi_config_t twiMpuConfig = {
       .scl                = MPU_SCL_PIN,
       .sda                = MPU_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    errorCode = nrf_drv_twi_init( &m_twiMpu, &twiMpuConfig, nullptr, nullptr );
    APP_ERROR_CHECK( errorCode );

    nrf_drv_twi_enable( &m_twiMpu );

    nrf_gpio_cfg_output( MPU_ADO_PIN );
    nrf_gpio_pin_set( MPU_ADO_PIN );

    constexpr std::uint8_t Mpu9250Addr = 0x69;
    std::uint8_t SampleData = 0x00;

    errorCode = nrf_drv_twi_rx( &m_twiMpu, Mpu9250Addr, &SampleData, sizeof( SampleData ) );

    if (errorCode == NRF_SUCCESS)
        Logger::Instance().logDebugEndl( "MPU9250 detected on address 0x69" );


    const nrf_drv_twi_config_t twiHeartConfig = {
       .scl                = HEARTRATE_SCL_PIN,
       .sda                = HEARTRATE_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    errorCode = nrf_drv_twi_init( &m_twiHeartrate, &twiHeartConfig, nullptr, nullptr );
    APP_ERROR_CHECK( errorCode );

    nrf_drv_twi_enable( &m_twiHeartrate );

    constexpr std::uint8_t Max30102Addr = 0x57;

    errorCode = nrf_drv_twi_rx( &m_twiHeartrate, Max30102Addr, &SampleData, sizeof( SampleData ) );

    if (errorCode == NRF_SUCCESS)
        Logger::Instance().logDebugEndl( "Max30102 detected on address 0x57" );
}

void
Application::runApplicationLoop()
{
    m_batteryLevelService->startBatteryMeasure();
    runTwiTest();
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
