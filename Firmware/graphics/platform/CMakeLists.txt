add_library(
    graphics_backend
    gs_platform_layer.cpp
)

target_link_libraries(
    graphics_backend
    PRIVATE
    lvgl_lib
    UtilsLibrary
    logger_service
    drivers_ih
    etl
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )

    target_compile_definitions(
        graphics_backend
        PRIVATE
        USE_HARDWARE_DISPLAY_BACKEND
    )

    target_link_libraries(
        graphics_backend
        PRIVATE
        watch_display
        NordicSDK::Common
        NordicSDK::App::Timer
    )
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR"  )
    target_compile_definitions(
        graphics_backend
        PRIVATE
        USE_WINSDL_BACKEND
    )
    target_link_libraries(
        graphics_backend
        PRIVATE
        lvgl_drivers
        fmt
    )
endif()

