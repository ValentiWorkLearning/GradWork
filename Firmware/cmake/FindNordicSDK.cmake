
message("<FindNordicSDK.cmake>")

if( NOT NRF5_SDK_PATH)
    message(ERROR " NRF5_SDK_PATH isn't defined!")
else()
    file(TO_CMAKE_PATH "${NRF5_SDK_PATH}" NRF5_SDK_PATH)
endif()

set ( SDK_DEPENDENT_DIR "defdir" CACHE PATH "Directory for SDK-dependent files for configuration")
set ( NRF52SOFTDEVICE "S132" CACHE STRING "SoftDevice version for NRF52 target")

add_library( NordicSDK::Common INTERFACE IMPORTED )


set ( NordicCompileDefinitions
    NRF52
    NRF52832
    NRF52832_XXAA
    NRF52_PAN_74
    NRF52_PAN_64
    NRF52_PAN_12
    NRF52_PAN_58
    NRF52_PAN_54
    NRF52_PAN_31
    NRF52_PAN_51
    NRF52_PAN_36
    NRF52_PAN_15
    NRF52_PAN_20
    NRF52_PAN_55
    BOARD_PCA10040
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

#Append softdevice-specific includes
if( NRF52SOFTDEVICE MATCHES "S132" )
    list( APPEND NordicCommonInc
        "${NRF5_SDK_PATH}/components/softdevice/s132/headers"
        "${NRF5_SDK_PATH}/components/softdevice/s132/headers/nrf52"
    )
elseif ( NRF52SOFTDEVICE MATCHES "S112" )
    list( APPEND NordicCommonInc
        "${NRF5_SDK_PATH}/components/softdevice/s112/headers"
        "${NRF5_SDK_PATH}/components/softdevice/s112/headers/nrf52"
    )

    list( APPEND NordicCompileDefinitions
        SOFTDEVICE_PRESENT
        S112
    )
endif()

#Append toolchain_specific CMSIS includes
list( APPEND NordicCommonInc "${NRF5_SDK_PATH}/components/toolchain/cmsis/include" )

#Append SDK_CONFIG for board
list( APPEND NordicCommonInc "${SDK_DEPENDENT_DIR}/config" )

#Append board pinout file
list( APPEND NordicCommonInc "${SDK_DEPENDENT_DIR}/board-pinout/" )

#Append SDK components headers
list(
    APPEND NordicCommonInc
    "${NRF5_SDK_PATH}/components/libraries/atomic"
    "${NRF5_SDK_PATH}/components/libraries/atomic_fifo"
    "${NRF5_SDK_PATH}/components/libraries/atomic_flags"
    "${NRF5_SDK_PATH}/components/libraries/balloc"
    "${NRF5_SDK_PATH}/components/libraries/bootloader/ble_dfu"
    "${NRF5_SDK_PATH}/components/libraries/cli"
    "${NRF5_SDK_PATH}/components/libraries/crc16"
    "${NRF5_SDK_PATH}/components/libraries/crc32"
    "${NRF5_SDK_PATH}/components/libraries/crypto"
    "${NRF5_SDK_PATH}/components/libraries/csense"
    "${NRF5_SDK_PATH}/components/libraries/csense_drv"
    "${NRF5_SDK_PATH}/components/libraries/delay"
    "${NRF5_SDK_PATH}/components/libraries/ecc"
    "${NRF5_SDK_PATH}/components/libraries/experimental_section_vars"
    "${NRF5_SDK_PATH}/components/libraries/experimental_task_manager"
    "${NRF5_SDK_PATH}/components/libraries/fds"
    "${NRF5_SDK_PATH}/components/libraries/fstorage"
    "${NRF5_SDK_PATH}/components/libraries/gfx"
    "${NRF5_SDK_PATH}/components/libraries/gpiote"
    "${NRF5_SDK_PATH}/components/libraries/hardfault"
    "${NRF5_SDK_PATH}/components/libraries/hci"
    "${NRF5_SDK_PATH}/components/libraries/led_softblink"
    "${NRF5_SDK_PATH}/components/libraries/log"
    "${NRF5_SDK_PATH}/components/libraries/log/src"
    "${NRF5_SDK_PATH}/components/libraries/low_power_pwm"
    "${NRF5_SDK_PATH}/components/libraries/mem_manager"
    "${NRF5_SDK_PATH}/components/libraries/memobj"
    "${NRF5_SDK_PATH}/components/libraries/mpu"
    "${NRF5_SDK_PATH}/components/libraries/mutex"
    "${NRF5_SDK_PATH}/components/libraries/pwm"
    "${NRF5_SDK_PATH}/components/libraries/pwr_mgmt"
    "${NRF5_SDK_PATH}/components/libraries/queue"
    "${NRF5_SDK_PATH}/components/libraries/ringbuf"
    "${NRF5_SDK_PATH}/components/libraries/scheduler"
    "${NRF5_SDK_PATH}/components/libraries/sdcard"
    "${NRF5_SDK_PATH}/components/libraries/slip"
    "${NRF5_SDK_PATH}/components/libraries/sortlist"
    "${NRF5_SDK_PATH}/components/libraries/spi_mngr"
    "${NRF5_SDK_PATH}/components/libraries/stack_guard"
    "${NRF5_SDK_PATH}/components/libraries/strerror"
    "${NRF5_SDK_PATH}/components/libraries/svc"
    "${NRF5_SDK_PATH}/components/libraries/timer"
    "${NRF5_SDK_PATH}/components/libraries/twi_mngr"
    "${NRF5_SDK_PATH}/components/libraries/twi_sensor"
    "${NRF5_SDK_PATH}/components/libraries/usbd"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/audio"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/cdc"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/cdc/acm"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/generic"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/kbd"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/hid/mouse"
    "${NRF5_SDK_PATH}/components/libraries/usbd/class/msc"
    "${NRF5_SDK_PATH}/components/libraries/util"
)


# Other external
list(
    APPEND NordicCommonInc
    "${NRF5_SDK_PATH}/external/fprintf/"
    "${NRF5_SDK_PATH}/external/utf_converter/"
)

# Segger RTT
list(
    APPEND NordicCommonInc
    "${NRF5_SDK_PATH}/external/segger_rtt/"
)

list(APPEND NRFSDK_INCLUDES ${NordicCommonInc} )


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


#Append SDK components headers
list(
    APPEND NordicCommonSrc
    "${NRF5_SDK_PATH}/components/libraries/atomic/nrf_atomic.c"
    "${NRF5_SDK_PATH}/components/libraries/atomic_fifo/nrf_atfifo.c"
    "${NRF5_SDK_PATH}/components/libraries/atomic_flags/nrf_atflags.c"
    "${NRF5_SDK_PATH}/components/libraries/balloc/nrf_balloc.c"
    "${NRF5_SDK_PATH}/components/libraries/experimental_section_vars/nrf_section_iter.c"
    "${NRF5_SDK_PATH}/components/libraries/hardfault/hardfault_implementation.c"
    "${NRF5_SDK_PATH}/components/libraries/util/nrf_assert.c"
    "${NRF5_SDK_PATH}/components/libraries/util/app_error.c"
    "${NRF5_SDK_PATH}/components/libraries/util/app_error_weak.c"
    "${NRF5_SDK_PATH}/components/libraries/util/app_error_handler_gcc.c"
    "${NRF5_SDK_PATH}/components/libraries/util/app_util_platform.c"
    "${NRF5_SDK_PATH}/components/libraries/util/sdk_mapped_flags.c"
    "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_flash.c"
    "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_rtt.c"
    "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_serial.c"
    "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_backend_uart.c"
    "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_default_backends.c"
    "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_frontend.c"
    "${NRF5_SDK_PATH}/components/libraries/log/src/nrf_log_str_formatter.c"
    "${NRF5_SDK_PATH}/components/libraries/memobj/nrf_memobj.c"
    "${NRF5_SDK_PATH}/components/libraries/pwr_mgmt/nrf_pwr_mgmt.c"
    "${NRF5_SDK_PATH}/components/libraries/ringbuf/nrf_ringbuf.c"
    "${NRF5_SDK_PATH}/components/libraries/strerror/nrf_strerror.c"
    "${NRF5_SDK_PATH}/components/libraries/uart/retarget.c"
    "${NRF5_SDK_PATH}/components/libraries/queue/nrf_queue.c"
)


list(APPEND NordicCommonSrc
    "${NRF5_SDK_PATH}/external/utf_converter/utf.c"
    "${NRF5_SDK_PATH}/external/fprintf/nrf_fprintf.c"
    "${NRF5_SDK_PATH}/external/fprintf/nrf_fprintf_format.c"
)

#Segger RTT
list(APPEND NordicCommonSrc
    "${NRF5_SDK_PATH}/external/segger_rtt/SEGGER_RTT_Syscalls_GCC.c"
    "${NRF5_SDK_PATH}/external/segger_rtt/SEGGER_RTT.c"
    "${NRF5_SDK_PATH}/external/segger_rtt/SEGGER_RTT_printf.c"
)

list(APPEND NordicCommonSrc
    "${NRF5_SDK_PATH}/modules/nrfx/mdk/system_nrf52.c"
    "${NRF5_SDK_PATH}/modules/nrfx/mdk/gcc_startup_nrf52.S"
)

set(CPU_FLAGS -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16)
set(COMMON_FLAGS -MP -MD -mthumb -mabi=aapcs -Wall -g3 -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums ${CPU_FLAGS})

target_include_directories(
    NordicSDK::Common
    INTERFACE
    ${NordicCommonInc}
)

target_compile_definitions(
    NordicSDK::Common
    INTERFACE
    ${NordicCompileDefinitions}
)


target_link_options(
    NordicSDK::Common
    INTERFACE
    ${CPU_FLAGS}
    -L${NRF5_SDK_PATH}/modules/nrfx/mdk
    -Wl,--gc-sections --specs=nano.specs -lc -lnosys -lm
)

target_compile_options(
    NordicSDK::Common INTERFACE
    --sysroot="${TOOLCHAIN_SYSROOT}"
    $<$<CONFIG:Debug>:-Og>
    $<$<CONFIG:Release>:-Os>
    ${COMMON_FLAGS}
)

target_sources(
    NordicSDK::Common
    INTERFACE
    ${NordicCommonSrc}
)

if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
set(TERMINAL "open")
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
set(TERMINAL "sh")
else()
set(TERMINAL "gnome-terminal")
endif()

function (nordicSdk_createBinAndHexFiles TARGET_NAME)
    add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${TARGET_NAME}.out
        COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET_NAME}.out "${TARGET_NAME}.bin"
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET_NAME}.out "${TARGET_NAME}.hex"
        COMMENT "post build steps for ${TARGET_NAME}"
    )
endfunction()

list(APPEND NRFSDK_INCLUDES ${NordicCommonInc} )
list(APPEND NRFSDK_SOURCES ${NordicCommonSrc} )

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(    NordicSDK
    FOUND_VAR NordicSDK_FOUND
    REQUIRED_VARS
    NRFSDK_INCLUDES
    NRFSDK_SOURCES
)