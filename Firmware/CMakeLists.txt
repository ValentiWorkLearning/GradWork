cmake_minimum_required(VERSION 3.14)

set( TARGET_PLATFORM "ARM_CORTEX" CACHE STRING "Target platform for application building")
message( "Current building platform is ${TARGET_PLATFORM}")

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH} )
    set(CPU_FLAGS -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16)
    set(COMMON_FLAGS 
        -MP -MD -mthumb -mabi=aapcs -Wall -g3 -ffunction-sections -fdata-sections -fno-strict-aliasing -fno-builtin --short-enums 
        ${CPU_FLAGS}
    )
    set( CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/cmake/arm-gcc-toolchain.cmake )
endif()

project(nordic-template C CXX ASM)

set (3RDPARTY_DIR "3rdparty")
add_subdirectory( ${3RDPARTY_DIR} ${CMAKE_BINARY_DIR}/3rdparty )


if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )

    set( NRF_TARGET "nrf52" )
    set( NRF52SOFTDEVICE "S112" )
    set( SDK_DEPENDENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/sdk_dependent")

    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
    add_subdirectory(cmake/nordic ${CMAKE_BINARY_DIR}/nrfsdk )
endif()

add_subdirectory(drivers)
add_subdirectory(utils)
add_subdirectory(logger)
add_subdirectory(graphics)
add_subdirectory(service_providers)

set (NORDIC_TARGET theOpenWatch)
add_executable(${NORDIC_TARGET} ${PROJECT_SOURCES})

target_sources(
    ${NORDIC_TARGET}
    PRIVATE
    main.cpp
    ap_application.cpp
)

target_link_libraries(
    ${NORDIC_TARGET}
    PRIVATE
    logger_service
    services_ih
    ble_factory
    drivers_ih
    watch_graphics
    graphics_backend
    watch_fake_services
    UtilsLibrary
    i2c
    watchboard
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(
        ${NORDIC_TARGET} PRIVATE
        ble_services
        NordicSDK::Common
    )

    target_compile_options(
        ${NORDIC_TARGET}
        PRIVATE
        -O0
        -fcoroutines
    )
endif()

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    set_target_properties( ${NORDIC_TARGET} PROPERTIES SUFFIX ".out" )
    option( EXECUTE_MCU_FLASHING "Execute binary flashing to target MCU" OFF )
    option( CREATE_NORDIC_FIRMWARE "Execute firmware bin and hex files creation" ON )

    if( CREATE_NORDIC_FIRMWARE )
        nordicSdk_createBinAndHexFiles( ${NORDIC_TARGET} )
    endif()

    if( EXECUTE_MCU_FLASHING )
        nordicSdk_flashSoftDevice( ${SOFTDEVICE_PATH} ${NRF_TARGET} )
        nordicSdk_flashFirmware( ${NORDIC_TARGET} )
    endif()
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )

    option( ENABLE_SANITIZE_BUILD "Build simultator with ASAN support" OFF)
    list(APPEND EXTRA_LIBS vcruntime user32 gdi32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32)
    target_compile_options( ${NORDIC_TARGET} PUBLIC /wd4576 /std:c++latest /await)

    if( ${ENABLE_SANITIZE_BUILD} )
        target_compile_options( ${NORDIC_TARGET} PUBLIC  /fsanitize=address )
    endif()

endif()


option(PACKAGE_TESTS "Build the tests" ON)
if(PACKAGE_TESTS)
    if( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
        enable_testing()
        add_subdirectory(firmware_tests)
    endif()
endif()