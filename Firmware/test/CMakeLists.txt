cmake_minimum_required(VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/arm-gcc-toolchain.cmake)

project(nordic-template C CXX ASM)

find_package(NordicSDK COMPONENTS Common REQUIRED)

include(CMakePrintHelpers)

add_executable(nordic-template.elf ${PROJECT_SOURCES})

target_link_options(
    nordic-template.elf
    PUBLIC
    --specs=nano.specs -lc -lnosys -lm
)

target_sources(
    nordic-template.elf
    PRIVATE
    main.c
)

target_link_options(
    nordic-template.elf
    PRIVATE
    -T ${SDK_DEPENDENT_DIR}/gcc_nrf52.ld
)

#cmake_print_properties( TARGETS nordic-template.elf PROPERTIES  LINK_DEPENDS )

target_link_libraries(
    nordic-template.elf
    NordicSDK::Common
    # Nordic::Libraries
    # Nordic::Ble::Battery
    # Nordic::Ble::Dts
)