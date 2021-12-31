cmake_minimum_required(VERSION 3.14)

set (TARGET_NAME lvgl_drivers)

add_library( ${TARGET_NAME} STATIC )

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_C_STANDARD 11)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    "lv_drivers/display/"
    "lv_drivers/indev/"
    "lv_drivers/"
    ${CMAKE_CURRENT_LIST_DIR}
)

set ( TARGET_SOURCE_LIST
    "lv_drivers/display/ILI9341.c"
    "lv_drivers/display/UC1610.c"
    "lv_drivers/display/GC9A01.c"
    "lv_drivers/display/SSD1963.c"
    "lv_drivers/display/drm.c"
    "lv_drivers/display/fbdev.c"
    "lv_drivers/display/SHARP_MIP.c"
    "lv_drivers/display/ST7565.c"
    "lv_drivers/display/R61581.c"
    "lv_drivers/indev/XPT2046.c"
    "lv_drivers/indev/FT5406EE8.c"
    "lv_drivers/indev/evdev.c"
    "lv_drivers/indev/xkb.c"
    "lv_drivers/indev/libinput.c"
    "lv_drivers/indev/AD_touch.c"
    "lv_drivers/win_drv.c"
    "lv_drivers/wayland/wayland.c"
    "lv_drivers/gtkdrv/gtkdrv.c"
    "lv_drivers/sdl/sdl_gpu.c"
    "lv_drivers/sdl/sdl.c"
    "lv_drivers/win32drv/win32drv.c"
)
target_sources(
    ${TARGET_NAME}
    PRIVATE
    ${TARGET_SOURCE_LIST}
)


set_source_files_properties(
    ${TARGET_SOURCE_LIST}
    PROPERTIES LANGUAGE C
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    lvgl_lib
)

if( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
    target_link_libraries(${TARGET_NAME} PUBLIC SDL2::SDL2)
endif()
