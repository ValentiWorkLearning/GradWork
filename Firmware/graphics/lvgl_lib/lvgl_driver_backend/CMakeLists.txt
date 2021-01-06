cmake_minimum_required(VERSION 3.14)

set (TARGET_NAME lvgl_drivers)

add_library( ${TARGET_NAME} STATIC )

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_C_STANDARD 11)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    "lv_drivers/display/fbdev.h"
    "lv_drivers/display/monitor.h"
    "lv_drivers/display/R61581.h"
    "lv_drivers/display/SHARP_MIP.h"
    "lv_drivers/display/SSD1963.h"
    "lv_drivers/display/ST7565.h"
    "lv_drivers/display/UC1610.h"
    "lv_drivers/indev/AD_touch.h"
    "lv_drivers/indev/evdev.h"
    "lv_drivers/indev/FT5406EE8.h"
    "lv_drivers/indev/keyboard.h"
    "lv_drivers/indev/libinput_drv.h"
    "lv_drivers/indev/mouse.h"
    "lv_drivers/indev/mousewheel.h"
    "lv_drivers/indev/XPT2046.h"
    "lv_drivers/lv_drv_conf_templ.h"
    "lv_drivers/win_drv.h"
    ${CMAKE_CURRENT_LIST_DIR}
)

set ( TARGET_SOURCE_LIST
    "lv_drivers/display/fbdev.c"
    "lv_drivers/display/monitor.c"
    "lv_drivers/display/R61581.c"
    "lv_drivers/display/SHARP_MIP.c"
    "lv_drivers/display/SSD1963.c"
    "lv_drivers/display/ST7565.c"
    "lv_drivers/display/UC1610.c"
    "lv_drivers/indev/AD_touch.c"
    "lv_drivers/indev/evdev.c"
    "lv_drivers/indev/FT5406EE8.c"
    "lv_drivers/indev/keyboard.c"
    "lv_drivers/indev/libinput.c"
    "lv_drivers/indev/mouse.c"
    "lv_drivers/indev/mousewheel.c"
    "lv_drivers/indev/XPT2046.c"
    "lv_drivers/win_drv.c"
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
target_link_libraries(${TARGET_NAME} PUBLIC CONAN_PKG::sdl2)