cmake_minimum_required(VERSION 3.14)
project(cppcoro LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

add_library(littlefs)

target_sources(littlefs PRIVATE
	"littlefs/lfs.c"
	"littlefs/lfs_util.c"
)

target_include_directories(littlefs PUBLIC 
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/littlefs>
)

target_compile_definitions(littlefs PUBLIC LFS_YES_TRACE)