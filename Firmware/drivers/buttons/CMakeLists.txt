add_library(
    buttons_driver
    bt_buttons_driver.cpp
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