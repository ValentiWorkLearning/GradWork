cmake_minimum_required(VERSION 3.14)
add_library(lvgl_fonts STATIC)


target_sources(
    lvgl_fonts
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/LcdNova12px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LcdNova16px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LcdNova24px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LcdNova30px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LcdNova36px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LcdNova68px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IconFont16px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IconFont24px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/IconFont35px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/PlayerIcons68px.cpp
)
target_link_libraries(lvgl_fonts PUBLIC lvgl_lib)