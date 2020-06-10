cmake_minimum_required(VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/arm-gcc-toolchain.cmake)

project(nordic-template C CXX ASM)

add_subdirectory(../cmake/nordic ${CMAKE_BINARY_DIR}/nrfsdk )
# find_package(NordicSDK COMPONENTS Common Ble AppButton REQUIRED)

set (NORDIC_TARGET nordic-template)
add_executable(${NORDIC_TARGET} ${PROJECT_SOURCES})
set_target_properties( ${NORDIC_TARGET} PROPERTIES SUFFIX ".out" )

set (3RDPARTY_DIR "../../3rdparty")
add_subdirectory( ${3RDPARTY_DIR} ${CMAKE_BINARY_DIR}/3rdparty )

set( NORDIC_TARGET_SOURCES_PATH "../Firmware/src")
add_subdirectory( ${NORDIC_TARGET_SOURCES_PATH}/graphics ${CMAKE_BINARY_DIR}/graphics_arm )

target_compile_definitions(
    ${NORDIC_TARGET}
    PRIVATE
    USE_ST7789V_BACKEND
    USE_NRFSDK_SIMULATOR
    USE_BLE_SERVICES
    USE_DEVICE_SPECIFIC
    LoggerSegger
)

target_compile_features(${NORDIC_TARGET} PUBLIC cxx_std_17)

target_sources(
    ${NORDIC_TARGET}
    PRIVATE
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/display/display_st7789v.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/spi/spi_wrapper.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/ble/ble_softdevice.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/ble/ble_custom_service.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/ble/ble_battery_service.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/ble/ble_datetime_service.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/factory_impl/ih_ble_service_factory.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/factory_impl/ih_ible_softdevice.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/factory_impl/ih_ble_service_factory.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/winbondflash/winbond_flash.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/service_providers/battery/sp_battery_service_fake.cpp # increase to 41960
    ${NORDIC_TARGET_SOURCES_PATH}/service_providers/heartrate/sp_heartrate_service_fake.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/service_providers/datetime/sp_datetime_service_fake.cpp # increase to 42158
    ${NORDIC_TARGET_SOURCES_PATH}/service_providers/sp_fake_services_creator.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/logger/logger_service_impl.cpp
    ${NORDIC_TARGET_SOURCES_PATH}/ap_application.cpp
)

target_include_directories(
    ${NORDIC_TARGET}
    PUBLIC
    ${3RDPARTY_DIR}/etl
    ${NORDIC_TARGET_SOURCES_PATH}/graphics
    ${NORDIC_TARGET_SOURCES_PATH}/drivers
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/ih
    ${NORDIC_TARGET_SOURCES_PATH}/drivers/ble
    ${NORDIC_TARGET_SOURCES_PATH}/utils
    ${NORDIC_TARGET_SOURCES_PATH}/logger
    ${NORDIC_TARGET_SOURCES_PATH}/service_providers

)

target_compile_options(
    ${NORDIC_TARGET}
    PRIVATE
    -Os
)

target_link_libraries(
    ${NORDIC_TARGET}

    etl
    watch_graphics
    lvgl_lib

    NordicSDK::Common

    NordicSDK::App::Scheduler
    NordicSDK::App::FIFO
    NordicSDK::App::Timer
    NordicSDK::App::Button

    NordicSDK::App::FDS
    NordicSDK::App::SensorSimulator

    NordicSDK::Ble
    NordicSDK::Ble::Gatt
    NordicSDK::Ble::GattQueue
    NordicSDK::Ble::ServiceDbDiscovery

    NordicSDK::Ble::PeerManager

    NordicSDK::BleService::LBS
    NordicSDK::BleService::BAS
    NordicSDK::BleService::CTSCLIENT
)

nordicSdk_createBinAndHexFiles( ${NORDIC_TARGET} )