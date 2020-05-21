cmake_minimum_required(VERSION 3.12)

project(E73DevBoard CXX ASM)

set (TARGET_NAME E73DevBoardBin)

# define some variables just for this example to determine file locations
set(NRF_PROJECT_NAME ble_app_blinky)
set(NRF_BOARD pca10040)
set(NRF_SOFTDEVICE s132)


# define some convenience variables to point to example project directories
set(NRF_CMAKE_CURRENT_LIST ${CMAKE_CURRENT_LIST_DIR})

set(NRF_PROJECT_PATH ${NRF_CMAKE_CURRENT_LIST}/..)
#set(NRF_PROJECT_PATH ${NRF5_SDK_PATH}/examples/ble_peripheral/${NRF_PROJECT_NAME})

set(NRF_PROJECT_DEVICE_PATH ${NRF_PROJECT_PATH}/sdk_dependent)
#set(NRF_PROJECT_DEVICE_PATH ${NRF_PROJECT_PATH}/${NRF_BOARD}/${NRF_SOFTDEVICE})

# you can specify the location of the linker script if desired instead of using a specific file name
set( NRF5_LINKER_SCRIPT ${NRF_PROJECT_PATH}/sdk_dependent/gcc_nrf52.ld )

nRF5x_setup()

nRF5x_addAppScheduler()
nRF5x_addAppFIFO()
nRF5x_addAppTimer()
nRF5x_addAppUART()
nRF5x_addAppButton()
nRF5x_addBSP(TRUE FALSE FALSE) # without this text size is 11 480, with this - 11 760

nRF5x_addBLEGATT() # with this text size = 11784
nRF5x_addBLEPeerManager() #with this text size is
nRF5x_addAppFDS() # 34312
nRF5x_addSensorSimulator() # still 34312
nRF5x_addBLEServiceDbDiscovery()
nRF5x_addBLEGattQueue()

nRF5x_addBLEService(ble_lbs) #still 34312
nRF5x_addBLEService(ble_bas) # increased to 34332
nRF5x_addBLEService(ble_cts_c)

add_definitions(-DCONFIG_GPIO_AS_PINRESET)

# usually you would include files in this directory here, like so:
#include_directories(.)
list(APPEND SOURCE_FILES main.cpp)

# for example projects we include the example source files
message( "Config include inside:" ${NRF_PROJECT_DEVICE_PATH}/config)
include_directories(${NRF_PROJECT_DEVICE_PATH}/config)
include_directories(${NRF_PROJECT_DEVICE_PATH}/board-pinout)
#list(APPEND SOURCE_FILES ${NRF_PROJECT_PATH}/main.c)

nRF5x_addExecutable(${TARGET_NAME} "${SOURCE_FILES}")


add_subdirectory ("graphics")

set (3RDPARTY_DIR "../../../3rdparty")
add_subdirectory( ${3RDPARTY_DIR} ${CMAKE_BINARY_DIR}/3rdparty )

target_compile_definitions(
    ${TARGET_NAME}
    PRIVATE
    USE_ST7789V_BACKEND
    USE_NRFSDK_SIMULATOR
    USE_BLE_SERVICES
    USE_DEVICE_SPECIFIC
    LoggerSegger
)

target_sources(
    ${TARGET_NAME}
    PRIVATE
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
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/LcdNova12px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/LcdNova16px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/LcdNova24px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/LcdNova30px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/LcdNova36px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/LcdNova68px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/IconFont16px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/IconFont24px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/IconFont35px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts/PlayerIcons68px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/gs_page_view_object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/gs_main_window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/gs_theme_controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/gs_event_dispatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets/battery/gs_battery_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets/battery/gs_battery_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets/pages_switch/gs_pages_switch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets/bluetooth/gs_bluetooth_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets/bluetooth/gs_bluetooth_widget_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets/gs_widget_base_obj.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/pages/clock_page/gs_clock_page_view.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/pages/clock_page/gs_clock_page_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/pages/health_page/gs_health_page_view.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/pages/player_page/gs_player_page_view.cpp
    ${CMAKE_CURRENT_LIST_DIR}/graphics/gs_lvgl_service.cpp # increase to 42664
    ${CMAKE_CURRENT_LIST_DIR}/graphics/gs_platform_layer.cpp # increase to 41864
    ${CMAKE_CURRENT_LIST_DIR}/service_providers/battery/sp_battery_service_fake.cpp # increase to 41960
    ${CMAKE_CURRENT_LIST_DIR}/service_providers/heartrate/sp_heartrate_service_fake.cpp
    ${CMAKE_CURRENT_LIST_DIR}/service_providers/datetime/sp_datetime_service_fake.cpp # increase to 42158
    ${CMAKE_CURRENT_LIST_DIR}/service_providers/sp_fake_services_creator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/logger/logger_service_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ap_application.cpp
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${3RDPARTY_DIR}/etl
    ${CMAKE_CURRENT_LIST_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/drivers/ih
    ${CMAKE_CURRENT_LIST_DIR}/drivers/ble
    ${CMAKE_CURRENT_LIST_DIR}/utils
    ${CMAKE_CURRENT_LIST_DIR}/logger
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/ih
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets/battery
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts
    ${CMAKE_CURRENT_LIST_DIR}/graphics/icons
    ${CMAKE_CURRENT_LIST_DIR}/service_providers
)

target_link_libraries(
    ${TARGET_NAME}
    lvgl_lib
    etl
)
