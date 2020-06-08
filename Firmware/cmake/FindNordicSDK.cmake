
message("<FindNordicSDK.cmake>")

if( NOT NRF5_SDK_PATH)
    message(ERROR "NRF5_SDK_PATH isn't defined!")
else()
    file(TO_CMAKE_PATH "${NRF5_SDK_PATH}" NRF5_SDK_PATH)
endif()


add_library( NordicSDK::Common INTERFACE IMPORTED )
target_compile_options( NordicSDK::Common INTERFACE 
        --sysroot="${TOOLCHAIN_SYSROOT}"
        -mthumb -mabi=aapcs -Wall -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
        $<$<CONFIG:Debug>:-Og>
        $<$<CONFIG:Release>:-Os>
    )

set (
    NordicCommonInc
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

list(APPEND NRFSDK_INCLUDES ${NordicCommonInc} )

#message("NRFSDK_INCLUDES = ${NRFSDK_INCLUDES}")
target_include_directories(
    NordicSDK::Common
    INTERFACE
    ${NordicCommonInc}
)

set (
    NordicCommonSrc
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

target_sources(
    NordicSDK::Common
    INTERFACE
    ${NordicCommonSrc}
)

list(APPEND NRFSDK_INCLUDES ${NordicCommonInc} )
list(APPEND NRFSDK_SOURCES ${NordicCommonSrc} )


# set(NordicSDK_FIND_COMPONENTS
#     Common
# )

#set(Common_FOUND TRUE)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(    NordicSDK
    FOUND_VAR NordicSDK_FOUND
    REQUIRED_VARS
    NRFSDK_INCLUDES
    NRFSDK_SOURCES
#    HANDLE_COMPONENTS
)