add_library(
    watch_display
    display_st7789v.cpp
)

target_include_directories(
    watch_display
    PUBLIC
    UtilsLibrary
    ${DRIVER_ROOT_DIR}/spi
    ${DRIVER_ROOT_DIR}/ih
    ${DRIVER_ROOT_DIR}/gpio
    ${DRIVER_ROOT_DIR}/platform_delay
    ${CMAKE_CURRENT_LIST_DIR}
)


target_link_libraries(
    watch_display
    PUBLIC
    UtilsLibrary
    platform_delay
    spi
    gpio
    etl
)