add_library(
    ble_factory
    ble_services_stub.cpp
    ih_ble_service_factory.cpp
    ih_ible_softdevice.cpp
)

target_compile_definitions(
    ble_factory
    PRIVATE
    USE_BLE_SERVICES
)

target_compile_features(
    ble_factory
    INTERFACE
    cxx_std_17
)

target_include_directories(
    ble_factory
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    ble_factory
    PRIVATE
    NordicSDK::Common
    UtilsLibrary
    drivers_ih
    logger_service
    ble_services
)