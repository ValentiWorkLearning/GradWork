cmake_minimum_required(VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/arm-gcc-toolchain.cmake)

project(nordic-template C CXX ASM)

find_package(NordicSDK COMPONENTS Common REQUIRED)

set(PROJECT_SOURCES
    main.c
)

add_executable(nordic-template.elf ${PROJECT_SOURCES})
target_link_libraries(
    nordic-template.elf
    Nordic::Common
    # Nordic::Libraries
    # Nordic::Ble::Battery
    # Nordic::Ble::Dts
)