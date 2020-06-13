add_library(
    ble_services
    ble_battery_service.cpp
    ble_custom_service.cpp
    ble_datetime_service.cpp
    ble_softdevice.cpp
)

target_compile_features(
    ble_services
    INTERFACE
    cxx_std_17
)

target_include_directories(
    ble_services
    PRIVATE
    ${DRIVER_ROOT_DIR}
    UtilsLibrary
)

target_link_libraries(
    ble_services
    PRIVATE
    NordicSDK::Ble
    NordicSDK::Bsp::BleButton
    NordicSDK::Ble::PeerManager
    NordicSDK::Ble::ServiceDbDiscovery
    NordicSDK::BleService::BAS
    NordicSDK::BleService::CTSCLIENT
    UtilsLibrary
    etl
    drivers_ih
    logger_service
)