message("<FindFreeRTOS.cmake>")

include(../nordic/nrfsdk_utils.cmake)

set( FREERTOS_PATH "C:/FreeRTOS" CACHE STRING "Directory of FreeRTOS" )

set (
    FreeRTOS_Include
    "${FREERTOS_PATH}/include"
)
set (FreeRTOS_Sources
    "${FREERTOS_PATH}/croutine.c"
    "${FREERTOS_PATH}/event_groups.c"
    "${FREERTOS_PATH}/list.c"
    "${FREERTOS_PATH}/queue.c"
    "${FREERTOS_PATH}/stream_buffer.c"
    "${FREERTOS_PATH}/tasks.c"
    "${FREERTOS_PATH}/timers.c"

    "${FREERTOS_PATH}/portable/MemMang/heap_5.c"
)

set (
    PORTABLE_FILES
    "${FREERTOS_PATH}/portable/GCC/"
)

list(APPEND ${FreeRTOS_Include} "${FREE_RTOS_CONFIG_DIR}" "${PORTABLE_FILES}" )
list(APPEND ${FreeRTOS_Include} "${FREERTOS_PATH}/portable/GCC/ARM_CM4F/")

add_library( FreeRTOS STATIC ${FreeRTOS_Sources} ${FreeRTOS_Include})
add_library( FreeRTOS::FreeRTOS ALIAS FreeRTOS)

target_include_directories(
    FreeRTOS
    PUBLIC
    "${FREERTOS_PATH}/include"
    "${FREE_RTOS_CONFIG_DIR}"
    "${PORTABLE_FILES}/ARM_CM4F/"
)

target_link_libraries(FreeRTOS PUBLIC NordicSDK::Common )

target_compile_options(
    FreeRTOS PUBLIC
    --sysroot="${TOOLCHAIN_SYSROOT}"
    $<$<CONFIG:Debug>:-Os>
    $<$<CONFIG:Release>:-O0>
    ${COMMON_FLAGS}
)

set( FREE_RTOS_PORTABLE_INC
    "${NRF5_SDK_PATH}/external/freertos/portable/GCC/nrf52"
    "${NRF5_SDK_PATH}/external/freertos/portable/CMSIS/nrf52"
)

set( FREE_RTOS_PORTABLE_SRC
    "${NRF5_SDK_PATH}/external/freertos/portable/GCC/nrf52/port.c"
    "${NRF5_SDK_PATH}/external/freertos/portable/CMSIS/nrf52/port_cmsis.c"
    "${NRF5_SDK_PATH}/external/freertos/portable/CMSIS/nrf52/port_cmsis_systick.c"
)

declareNordicSdkLibrary(
    External_FreeRtosPortable
    "${FREE_RTOS_PORTABLE_INC}"
    "${FREE_RTOS_PORTABLE_SRC}"
    FreeRTOS::FreeRTOS
    NordicSDK::Common
)