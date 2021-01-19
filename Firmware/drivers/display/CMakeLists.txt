add_library(
    watch_display
    display_st7789v.cpp
    display_gc9a01.cpp
    display_coro_gc9a01.cpp
    display_creator.cpp
    display_coro_compact_gc9a01.cpp
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
    logger_service
)


if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_compile_definitions(
        watch_display
        PRIVATE
        USE_GC9A01_COMPACT_CORO_BACKEND
    )

    target_link_libraries(watch_display
        PRIVATE
        NordicSDK::Common
    )
endif()