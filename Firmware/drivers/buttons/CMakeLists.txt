add_library(
    buttons_driver
    
    
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
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
    if(WIN32)
        target_sources(
            buttons_driver
            PRIVATE
            bt_os_win32_hardware_buttons_manual_backend.cpp
        )
    elseif(UNIX)
        target_sources(
            buttons_driver
            PRIVATE
            bt_os_stub_hardware_buttons_backend.cpp
        )
    endif()
endif()