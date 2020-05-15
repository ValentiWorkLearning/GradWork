cmake_minimum_required(VERSION 3.12)

option( EXECUTE_MCU_FLASHING "Execute binary flashingto target MCU" ON )
option( USE_ENV_SDK_PATH "Use Nordic SDK path from Environment variables" ON )

set(NRF_TARGET nrf52)

if (NOT DEFINED ARM_NONE_EABI_TOOLCHAIN_PATH)
	set(ARM_NONE_EABI_TOOLCHAIN_PATH "C:/gcc_none_eabi_9_2_1")
endif ()

if ( USE_ENV_SDK_PATH )
	set(NRF5_SDK_PATH $ENV{NRF5_SDK_PATH_ENV})
else()
	message("Current NRF5_SDK_PATH_EXT is" ${NRF5_SDK_PATH_EXT})
	set(NRF5_SDK_PATH ${NRF5_SDK_PATH_EXT})
endif()


if( EXECUTE_MCU_FLASHING )
	set(NRFJPROG $ENV{NRFJPROG_PATH}/nrfjprog.exe )
endif(EXECUTE_MCU_FLASHING)

include("${CMAKE_CURRENT_LIST_DIR}/../CMake_nRF5x.cmake")

nRF5x_toolchainSetup()

project(ExampleProject C)

add_subdirectory(src)