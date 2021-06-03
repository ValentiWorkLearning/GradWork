set (TARGET_NAME ble_services )

add_library(
    ${TARGET_NAME}
    ${TARGET_SOURCE}
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

    target_include_directories(
        ${TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/inc
    )

    target_link_libraries(
        ${TARGET_NAME}
        PUBLIC
        NordicSDK::Ble
        NordicSDK::App::FDS
        NordicSDK::Bsp::BleButton
        NordicSDK::Ble::PeerManager
        NordicSDK::Ble::ServiceDbDiscovery
        NordicSDK::BleService::BateryService
        NordicSDK::BleService::CurrentTimeClient
        NordicSDK::BleService::HeartrateService
    )

    target_sources(
        ${TARGET_NAME}
        PRIVATE
        ble_custom_service.cpp
        ble_softdevice.cpp
        ble_battery_service.cpp
        ble_datetime_service.cpp
        ble_heartrate_service.cpp
    )
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
    target_include_directories(
        ${TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/inc/ble
    )
    target_sources(
        ${TARGET_NAME}
        PRIVATE
        ble_desktop_softdevice.cpp
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
