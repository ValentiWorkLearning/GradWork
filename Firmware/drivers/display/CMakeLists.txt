add_library(
    watch_display
    display_st7789v.cpp
    display_creator.cpp
)

target_compile_definitions(
    watch_display
    PRIVATE
    USE_ST7789V_BACKEND
)


target_include_directories(
    watch_display
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_include_directories(
    watch_display
    PRIVATE
    UtilsLibrary
    ${CMAKE_CURRENT_LIST_DIR}
)


target_link_libraries(
    watch_display
    PUBLIC
    spi
    UtilsLibrary
    drivers_ih
    platform_delay
    gpio
    etl
)