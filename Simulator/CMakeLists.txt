cmake_minimum_required(VERSION 3.12)

set (TARGET_NAME WatchSim )

project(FirmwareSimulator)



set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_compile_options(/wd4576)

if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    else()
        set_target_properties(
            ${TARGET_NAME}
            PROPERTIES
            CXX_STANDARD 17
        )
    endif()
endif()

add_subdirectory ("graphics")
add_subdirectory("graphics/SDL-mirror")

add_executable(
    ${TARGET_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../Firmware/Firmware/src/graphics/widgets_layer/lvgl_ui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../Firmware/Firmware/src/graphics/fonts/RobotoFont40px.cpp
)

target_compile_definitions(
    ${TARGET_NAME}
    PUBLIC
    SDL_MAIN_HANDLED
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    "graphics/SDL-mirror/include"
    ${CMAKE_CURRENT_LIST_DIR}/../Firmware/Firmware/src/graphics/widgets_layer
    ${CMAKE_CURRENT_LIST_DIR}/../Firmware/Firmware/src/graphics/fonts
)

target_link_libraries(
    ${TARGET_NAME}
    SDL2
    lvgl_lib
)
