#include "inc/i2c/i2c_test.hpp"

#include "pca10040.h"
#include "utils/MetaUtils.hpp"

#include "nrf_drv_twi.h"

#include "logger/logger_service.hpp"

namespace I2C
{
void scanI2CSensors()
{
    #if defined (USE_DEVICE_SPECIFIC)
    static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(0);

    ret_code_t errorCode{};

    const nrf_drv_twi_config_t twiMpuConfig = {
       .scl                = MPU_SCL_PIN,
       .sda                = MPU_SDA_PIN,
       .frequency          = NRF_DRV_TWI_FREQ_100K,
       .interrupt_priority = APP_IRQ_PRIORITY_HIGH,
       .clear_bus_init     = false
    };

    errorCode = nrf_drv_twi_init( &m_twi, &twiMpuConfig, nullptr, nullptr );
    APP_ERROR_CHECK( errorCode );

    nrf_drv_twi_enable( &m_twi );

    nrf_gpio_cfg_output( MPU_ADO_PIN );
    nrf_gpio_pin_set( MPU_ADO_PIN );

    constexpr std::uint8_t Mpu9250Addr = 0x69;
    std::uint8_t SampleData = 0x00;

    errorCode = nrf_drv_twi_rx( &m_twi, Mpu9250Addr, &SampleData, sizeof( SampleData ) );

    if (errorCode == NRF_SUCCESS)
        Logger::Instance().logDebugEndl( "MPU9250 detected on address 0x69" );

    constexpr std::uint8_t Max30102Addr = 0x57;

    errorCode = nrf_drv_twi_rx( &m_twi, Max30102Addr, &SampleData, sizeof( SampleData ) );

    if (errorCode == NRF_SUCCESS)
        Logger::Instance().logDebugEndl( "Max30102 detected on address 0x57" );
#endif
}

};
