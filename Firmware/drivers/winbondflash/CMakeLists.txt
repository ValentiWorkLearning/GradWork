add_library(
    windbond_spi_flash_driver
    winbond_driver_creator.cpp
    )

target_include_directories(
    windbond_spi_flash_driver
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    windbond_spi_flash_driver
    PRIVATE
    UtilsLibrary
    logger_service
    platform_delay
    drivers_ih
    spi
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(windbond_spi_flash_driver
        PRIVATE
        NordicSDK::Common
        NordicSDK::Bsp
        NordicSDK::App::Timer
    )

    target_compile_definitions(
        windbond_spi_flash_driver
        PRIVATE
        USE_DEVICE_SPECIFIC
    )
    target_sources(
        windbond_spi_flash_driver
        PRIVATE
        winbond_flash.cpp
    )
# elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
#     target_sources(
#         windbond_spi_flash_driver
#         PRIVATE
#         bt_win32_hardware_buttons_manual_backend.cpp
#     )
endif()