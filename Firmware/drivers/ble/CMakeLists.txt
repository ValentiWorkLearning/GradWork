set (TARGET_NAME ble_services )

add_library(
    ${TARGET_NAME}
    ble_battery_service.cpp
    ble_custom_service.cpp
    ble_datetime_service.cpp
    ble_softdevice.cpp
)

target_compile_features(
    ${TARGET_NAME}
    INTERFACE
    cxx_std_17
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    ${TARGET_NAME}
    PUBLIC
    UtilsLibrary
    etl
    drivers_ih
    logger_service
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(
        ${TARGET_NAME}
        PUBLIC
        NordicSDK::Ble
        NordicSDK::App::FDS
        NordicSDK::Bsp::BleButton
        NordicSDK::Ble::PeerManager
        NordicSDK::Ble::ServiceDbDiscovery
        NordicSDK::BleService::BAS
        NordicSDK::BleService::CTSCLIENT
    )
endif()

target_link_options(
    ${TARGET_NAME}
    PUBLIC
    ${CPU_FLAGS}
)

target_compile_options(
    ${TARGET_NAME}
    PUBLIC
    -Os
    ${COMMON_FLAGS}
)
