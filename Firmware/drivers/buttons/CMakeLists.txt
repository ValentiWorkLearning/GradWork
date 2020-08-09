add_library(
    buttons_driver
    bt_buttons_driver.cpp
    bt_buttons_driver_creator.cpp
)

target_include_directories(
    buttons_driver
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    buttons_driver
    PRIVATE
    UtilsLibrary
    logger_service
    platform_delay
    drivers_ih
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_sources(
        buttons_driver
        PRIVATE
        bt_nordic_hardware_backend.cpp
    )
    target_link_libraries(buttons_driver
        PRIVATE
        NordicSDK::Common
        NordicSDK::Bsp
        NordicSDK::App::Timer
    )

    target_compile_definitions(
        buttons_driver
        PRIVATE
        USE_DEVICE_SPECIFIC
    )
endif()