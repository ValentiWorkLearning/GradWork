cmake_minimum_required(VERSION 3.14)

add_library(littlefs)

target_sources(littlefs PRIVATE
	littlefs/lfs.cpp
	littlefs/lfs_util.cpp
 "lfs_util_desktop.h")

target_include_directories(littlefs PUBLIC littlefs
)

target_link_libraries(littlefs PUBLIC UtilsLibrary )

target_compile_definitions(littlefs PUBLIC LFS_YES_TRACE )

target_link_options(
    littlefs
    PUBLIC
    ${CPU_FLAGS}
)

target_compile_options(
    littlefs
    PUBLIC
    ${COMMON_FLAGS}
)

target_compile_options(
    littlefs
    PUBLIC
    $<$<CXX_COMPILER_ID:GNU>:-Os>
)

target_include_directories(littlefs PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_precompile_headers(littlefs PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lfs_util_segger.h)
    target_link_libraries(littlefs PRIVATE NordicSDK::Common)
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR")
    target_precompile_headers(littlefs PRIVATE ${CMAKE_CURRENT_LIST_DIR}/lfs_util_desktop.h)
    target_link_libraries(littlefs PUBLIC logger_service)
endif()
