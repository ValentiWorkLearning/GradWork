cmake_minimum_required(VERSION 3.12)

set(NRF_TARGET nrf52)

if (NOT DEFINED ARM_NONE_EABI_TOOLCHAIN_PATH)
	set(ARM_NONE_EABI_TOOLCHAIN_PATH "C:/gcc_none_eabi")
endif ()

set(NRF5_SDK_PATH $ENV{NRF5_SDK_PATH})
set(NRFJPROG $ENV{NRFJPROG_PATH}/nrfjprog.exe )

include("${CMAKE_CURRENT_LIST_DIR}/../CMake_nRF5x.cmake")

nRF5x_toolchainSetup()

project(ExampleProject C)

add_subdirectory(src)