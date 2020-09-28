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

target_compile_features(
    watchboard
    PRIVATE
    cxx_std_20
)

target_compile_options(
    watchboard
    PRIVATE
    -fcoroutines
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(watchboard
        PRIVATE
        NordicSDK::Common
        NordicSDK::Bsp
        NordicSDK::App::Timer

        windbond_spi_flash_driver
    )

    target_compile_definitions(
        watchboard
        PRIVATE
        USE_DEVICE_SPECIFIC
    )
endif()
