cmake_minimum_required(VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/arm-gcc-toolchain.cmake)

project(nordic-template C CXX ASM)

find_package(NordicSDK COMPONENTS Common Ble AppButton REQUIRED)

set (NORDIC_TARGET nordic-template)
add_executable(${NORDIC_TARGET} ${PROJECT_SOURCES})
set_target_properties( ${NORDIC_TARGET} PROPERTIES SUFFIX ".out" )

target_sources(
    ${NORDIC_TARGET}
    PRIVATE
    main.cpp
)

target_compile_options(
    ${NORDIC_TARGET}
    PRIVATE
    -Os
)

target_link_libraries(
    ${NORDIC_TARGET}

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
    NordicSDK::BleService::CTS_C
)

nordicSdk_createBinAndHexFiles( ${NORDIC_TARGET} )