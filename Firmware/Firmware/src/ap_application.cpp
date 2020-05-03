#include "ap_application.hpp"

#if defined (USE_BLE_SERVICES)
    #include "drivers/ble/ble_custom_service.hpp"
    #include "drivers/ble/ble_softdevice.hpp"
#endif

#if defined (USE_DEVICE_SPECIFIC)
#include "nrf_delay.h"
#include "nrf.h"
#include "boards.h"
#include "bsp.h"
#include "nrf_drv_twi.h"

#include "drivers/spi/spi_wrapper.hpp"
#include "drivers/winbondflash/winbond_flash.hpp"

#endif

#include "logger_service.hpp"
#include "graphics/gs_lvgl_service.hpp"
#include "graphics/gs_platform_layer.hpp"

#include "graphics/widgets_layer/ih/gs_imain_window.hpp"
#include "graphics/widgets_layer/gs_event_dispatcher.hpp"

#include "SimpleSignal.hpp"


Application::Application()
{
    initBoard();
    initInterfaces();
    initPeripheral();
    initServices();
    initGraphicsStack();
    initBleStack();
}

Application::~Application() = default;

void
Application::initInterfaces()
{

}

void
Application::initBoard()
{

#if defined (USE_DEVICE_SPECIFIC)
    /* Configure board. */
    bsp_board_init( BSP_INIT_LEDS );

    Logger::Instance().logDebugEndl( "Hello from E73 Mod Board!" );

    ret_code_t errorCode{};

    errorCode = app_timer_init();
    APP_ERROR_CHECK( errorCode );
#endif

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
#if defined (USE_DEVICE_SPECIFIC)
    auto pSpiInstance = Interface::Spi::createSpiBus<Interface::Spi::SpiInstance::M1>();
    auto pWindbondFlash= ExternalFlash::createFlashDriver(
        pSpiInstance.get()
    );
    pWindbondFlash->onBlockWriteCompleted.emit();
#endif
}

void
Application::initBleStack()
{

#if defined (USE_BLE_SERVICES)
    m_bleStackKeeper = Ble::Stack::createBleStackKeeper();

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

#endif

}

void
Application::initGraphicsStack()
{
    m_graphicsService = Graphics::createGraphicsService(
        Graphics::createPlatformBackend()
    );

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
Application::runTwiTest()
{
#if defined (USE_DEVICE_SPECIFIC)
    // static const nrf_drv_twi_t m_twiHeartrate = NRF_DRV_TWI_INSTANCE(0);
    static const nrf_drv_twi_t m_twiMpu = NRF_DRV_TWI_INSTANCE(0);

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


    // const nrf_drv_twi_config_t twiHeartConfig = {
    //    .scl                = HEARTRATE_SCL_PIN,
    //    .sda                = HEARTRATE_SDA_PIN,
    //    .frequency          = NRF_DRV_TWI_FREQ_100K,
    //    .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
    //    .clear_bus_init     = false
    // };

    // errorCode = nrf_drv_twi_init( &m_twiHeartrate, &twiHeartConfig, nullptr, nullptr );
    // APP_ERROR_CHECK( errorCode );

    // nrf_drv_twi_enable( &m_twiHeartrate );

    // constexpr std::uint8_t Max30102Addr = 0x57;

    // errorCode = nrf_drv_twi_rx( &m_twiHeartrate, Max30102Addr, &SampleData, sizeof( SampleData ) );

    // if (errorCode == NRF_SUCCESS)
    //     Logger::Instance().logDebugEndl( "Max30102 detected on address 0x57" );
#endif
}

void
Application::runApplicationLoop()
{
    m_batteryLevelService->startBatteryMeasure();
    m_dateTimeService->launchService();

    #if defined (USE_DEVICE_SPECIFIC)
    runTwiTest();
    /* Toggle LEDs. */
    Logger::Instance().logDebugEndl( "Led toggle..." );
    auto ledToggler =
    []( size_t _delayTime )
    {
        bsp_board_led_invert(0);
        nrf_delay_ms( _delayTime );
    };
    #endif
    while (true)
    {
    #if defined (USE_DEVICE_SPECIFIC)
        ledToggler( 300 );
    #endif
        m_graphicsService->executeGlTask();

        Simple::Lib::ExecuteLaterPool::Instance().processQueue();
    }
}
