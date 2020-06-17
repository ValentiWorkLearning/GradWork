cmake_minimum_required(VERSION 3.12)

set (TARGET_NAME watch_graphics)

add_library( ${TARGET_NAME} STATIC )

add_subdirectory (lvgl_lib)
add_subdirectory (platform)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/graphics/ih/widgets
    ${CMAKE_CURRENT_LIST_DIR}/graphics/ih/pages
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer
    ${CMAKE_CURRENT_LIST_DIR}/graphics/widgets_layer/widgets
    ${CMAKE_CURRENT_LIST_DIR}/graphics/fonts
    ${CMAKE_CURRENT_LIST_DIR}/graphics/icons
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(
    ${TARGET_NAME}
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/fonts/LcdNova12px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/LcdNova16px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/LcdNova24px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/LcdNova30px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/LcdNova36px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/LcdNova68px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/IconFont16px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/IconFont24px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/IconFont35px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/fonts/PlayerIcons68px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/gs_page_view_object.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/widgets/battery/gs_battery_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/widgets/battery/gs_battery_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/widgets/pages_switch/gs_pages_switch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/widgets/bluetooth/gs_bluetooth_widget.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/widgets/bluetooth/gs_bluetooth_widget_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/widgets/gs_widget_base_obj.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/pages/clock_page/gs_clock_page_view.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/pages/clock_page/gs_clock_page_handler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/pages/health_page/gs_health_page_view.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/pages/player_page/gs_player_page_view.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/gs_main_window.cpp
    ${CMAKE_CURRENT_LIST_DIR}/widgets_layer/gs_main_window_view.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gs_theme_controller.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gs_event_dispatcher.cpp
    ${CMAKE_CURRENT_LIST_DIR}/gs_lvgl_service.cpp
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    lvgl_lib
    etl
    UtilsLibrary
    logger_service
    graphics_backend
)

target_link_options(
    ${TARGET_NAME}
    PUBLIC
    ${CPU_FLAGS}
)

target_compile_options(
    ${TARGET_NAME}
    PUBLIC
    $<$<CONFIG:Debug>:-Os>
    $<$<CONFIG:Release>:-Os>
    ${COMMON_FLAGS}
)
