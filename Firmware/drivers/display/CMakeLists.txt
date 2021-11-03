add_library(
    watch_display
    INTERFACE
)

target_include_directories(
    watch_display
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_include_directories(
    watch_display
    INTERFACE
    UtilsLibrary
    ${CMAKE_CURRENT_LIST_DIR}
)


target_link_libraries(
    watch_display
    INTERFACE
    spi
    UtilsLibrary
    drivers_ih
    platform_delay
    gpio
    etl
    logger_service
)