add_library(
    watchboard
    watchboard.cpp
)

target_include_directories(
    watchboard
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    watchboard
    PRIVATE
    UtilsLibrary
    logger_service
    platform_delay
    drivers_ih
    buttons_driver
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(watchboard
        PRIVATE
        NordicSDK::Common
        NordicSDK::Bsp
        NordicSDK::App::Timer
    )

    target_compile_definitions(
        watchboard
        PRIVATE
        USE_DEVICE_SPECIFIC
    )
endif()