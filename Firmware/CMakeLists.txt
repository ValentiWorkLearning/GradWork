cmake_minimum_required(VERSION 3.8)

set( NRF52SOFTDEVICE "S112" )
set( SDK_DEPENDENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdk_dependent")

set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake)

project(nordic-template C CXX ASM)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CPU_FLAGS -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16)
set(COMMON_FLAGS 
    -MP -MD -mthumb -mabi=aapcs -Wall -g3 -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums 
    ${CPU_FLAGS}
)


set (3RDPARTY_DIR "../3rdparty")
add_subdirectory( ${3RDPARTY_DIR} ${CMAKE_BINARY_DIR}/3rdparty )

add_subdirectory(cmake/nordic ${CMAKE_BINARY_DIR}/nrfsdk )
add_subdirectory(drivers)
add_subdirectory(utils)
add_subdirectory(logger)
add_subdirectory(graphics)
add_subdirectory(service_providers)

set (NORDIC_TARGET theOpenWatch)
add_executable(${NORDIC_TARGET} ${PROJECT_SOURCES})
set_target_properties( ${NORDIC_TARGET} PROPERTIES SUFFIX ".out" )

target_sources(
    ${NORDIC_TARGET}
    PRIVATE
    main.cpp
    ap_application.cpp
)

target_compile_definitions(
    ${NORDIC_TARGET}
    PRIVATE
    USE_BLE_SERVICES
)

target_compile_options(
    ${NORDIC_TARGET}
    PRIVATE
    -Os
)

target_link_libraries(
    ${NORDIC_TARGET}
    ble_services
    logger_service
    services_ih
    ble_factory
    drivers_ih
    watch_graphics
    graphics_backend
    watch_fake_services
    UtilsLibrary
    NordicSDK::Common
)
nordicSdk_createBinAndHexFiles( ${NORDIC_TARGET} )