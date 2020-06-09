cmake_minimum_required(VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/../cmake/arm-gcc-toolchain.cmake)

project(nordic-template C CXX ASM)

find_package(NordicSDK COMPONENTS Common REQUIRED)

set (NORDIC_TARGET nordic-template)
add_executable(${NORDIC_TARGET} ${PROJECT_SOURCES})
set_target_properties( ${NORDIC_TARGET} PROPERTIES SUFFIX ".out" )

target_link_options(
    ${NORDIC_TARGET}
    PUBLIC
    --specs=nano.specs -lc -lnosys -lm
    -Wl,-Map=${NORDIC_TARGET}.map
    -T ${SDK_DEPENDENT_DIR}/gcc_nrf52.ld
)

target_sources(
    ${NORDIC_TARGET}
    PRIVATE
    main.c
)

target_link_libraries(
    ${NORDIC_TARGET}
    NordicSDK::Common
    # Nordic::Libraries
    # Nordic::Ble::Battery
    # Nordic::Ble::Dts
)

nordicSdk_createBinAndHexFiles( ${NORDIC_TARGET} )