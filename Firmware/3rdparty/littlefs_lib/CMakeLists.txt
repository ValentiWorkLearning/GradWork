cmake_minimum_required(VERSION 3.14)

add_library(littlefs)

target_sources(littlefs PRIVATE
	littlefs/lfs.cpp
	littlefs/lfs_util.cpp
)

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
