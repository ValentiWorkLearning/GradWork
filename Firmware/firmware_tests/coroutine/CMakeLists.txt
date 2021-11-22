cmake_minimum_required(VERSION 3.14)

project(coroutine_experiments C CXX)

if( UNIX )
    find_package(Threads REQUIRED)
endif()

add_executable(coroutine_experiments_app ${PROJECT_SOURCES})

target_sources(
    coroutine_experiments_app
    PRIVATE
    coroutine_thoughts.cpp
    thoughts.hpp
    st7789_draft.hpp
    fs_ideas/filesystem_holder.hpp
    
    fs_ideas/platform_filesystem.hpp
    wrapper/ih_block_device.hpp
    wrapper/heap_block_device.hpp
)

target_include_directories(
    coroutine_experiments_app
    PRIVATE
    fs_ideas
    wrapper
)
target_compile_features(
    coroutine_experiments_app
    PRIVATE
    cxx_std_20
)

if(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /fsanitize=address")
else()
    set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
    set (CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fno-omit-frame-pointer -fsanitize=address")
endif()

target_link_libraries(
    coroutine_experiments_app
    PRIVATE
    drivers_ih
    watch_display
    UtilsLibrary
    logger_service
    littlefs
)
if(UNIX)
    target_link_libraries( coroutine_experiments_app PUBLIC Threads::Threads)
endif()
