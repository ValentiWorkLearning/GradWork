if( NOT NRF5_SDK_PATH)
    message(ERROR "NRF5_SDK_PATH isn't defined!")
else()
    file(TO_CMAKE_PATH "${NRF5_SDK_PATH}" NRF5_SDK_PATH)
endif()


add_library( NordicSdk::Common INTERFACE IMPORTED )
target_compile_options( NordicSdk::Common INTERFACE 
        --sysroot="${TOOLCHAIN_SYSROOT}"
        -mthumb -mabi=aapcs -Wall -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Release>:-Os>
    )

target_include_directories(
    NordicSdk::Common
    PUBLIC
    "${NRF5_SDK_PATH}/components"
    "${NRF5_SDK_PATH}/components/boards"
    "${NRF5_SDK_PATH}/components/softdevice/common"
    "${NRF5_SDK_PATH}/integration/nrfx"
    "${NRF5_SDK_PATH}/integration/nrfx/legacy"
    "${NRF5_SDK_PATH}/modules/nrfx"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/include"
    "${NRF5_SDK_PATH}/modules/nrfx/hal"
    "${NRF5_SDK_PATH}/modules/nrfx/mdk" 
)

target_sources(
    NordicSdk::Common
    PUBLIC
    "${NRF5_SDK_PATH}/modules/nrfx/mdk/system_nrf52.c"
    "${NRF5_SDK_PATH}/components/boards/boards.c"
    "${NRF5_SDK_PATH}/components/softdevice/common/nrf_sdh.c"
    "${NRF5_SDK_PATH}/components/softdevice/common/nrf_sdh_soc.c"
    "${NRF5_SDK_PATH}/integration/nrfx/legacy/nrf_drv_clock.c"
    "${NRF5_SDK_PATH}/integration/nrfx/legacy/nrf_drv_uart.c"
    "${NRF5_SDK_PATH}/integration/nrfx/legacy/nrf_drv_twi.c"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_clock.c"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_gpiote.c"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_uart.c"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_spim.c"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_twim.c"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/nrfx_uarte.c"
    "${NRF5_SDK_PATH}/modules/nrfx/drivers/src/prs/nrfx_prs.c"
    "${NRF5_SDK_PATH}/modules/nrfx/soc/nrfx_atomic.c"
)

target_compile_definitions(
    NordicSdk::Common INTERFACE
    SOFTDEVICE_PRESENT
    S112
    SWI_DISABLE0
    BLE_STACK_SUPPORT_REQD
    DNRF_SD_BLE_API_VERSION=6
    DENABLE_SWO
)

target_link_options(
    NordicSdk::Common INTERFACE 
    --sysroot="${TOOLCHAIN_SYSROOT}"
    -mthumb -mabi=aapcs -Wl,--gc-sections
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Release>:-Os -s>
)