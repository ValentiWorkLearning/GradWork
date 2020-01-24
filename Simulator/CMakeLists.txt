cmake_minimum_required(VERSION 3.12)

set (TARGET_NAME WatchSim )

project(FirmwareSimulator)

find_package(Boost 1.68.0)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(APPEND EXTRA_LIBS vcruntime user32 gdi32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32)

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

set (FIRMWARE_SRC_DIR "/../Firmware/Firmware/src/")

add_executable(
    ${TARGET_NAME}
    ${CMAKE_CURRENT_LIST_DIR}/src/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/widgets_layer/lvgl_ui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/fonts/LcdNova16px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/fonts/LcdNova40px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/fonts/LcdNova72px.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/icons/HeartrateIcon.c
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/gs_platform_layer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/gs_lvgl_service.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/service_providers/battery/sp_battery_service_fake.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/service_providers/heartrate/sp_heartrate_service_fake.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/service_providers/sp_fake_services_creator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/logger/logger_service_impl.cpp
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/ap_application.cpp
)

target_compile_definitions(
    ${TARGET_NAME}
    PUBLIC
    SDL_MAIN_HANDLED
    USE_DESKTOP_SIMULATOR
    USE_WINSDL_BACKEND
    LoggerDesktop
)

target_include_directories(
    ${TARGET_NAME}
    PUBLIC
    "graphics/SDL-mirror/include"
    ${Boost_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/drivers
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/widgets_layer
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/fonts
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/graphics/icons
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/utils
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/logger
    ${CMAKE_CURRENT_LIST_DIR}/${FIRMWARE_SRC_DIR}/service_providers
)

target_link_libraries(
    ${TARGET_NAME}
    SDL2
    lvgl_lib
    ${Boost_LIBRARIES}
)
