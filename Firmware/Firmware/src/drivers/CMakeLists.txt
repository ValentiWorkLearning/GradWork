

add_library(
    drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/display/display_st7789v.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/spi/spi_wrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/ble/ble_softdevice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/ble/ble_custom_service.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/ble/ble_battery_service.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/ble/ble_datetime_service.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/factory_impl/ih_ble_service_factory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/factory_impl/ih_ible_softdevice.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/factory_impl/ih_ble_service_factory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/drivers/winbondflash/winbond_flash.cpp
)