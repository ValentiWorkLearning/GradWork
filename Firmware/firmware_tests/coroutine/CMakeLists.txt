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
)

target_compile_features(
    coroutine_experiments_app
    PRIVATE
    cxx_std_20
)

if( ${ENABLE_SANITIZE_BUILD} )
        target_compile_options( coroutine_experiments_app PRIVATE /fsanitize=address )
    endif()

target_link_libraries(
    coroutine_experiments_app
    PRIVATE
    drivers_ih
    watch_display
    UtilsLibrary
    logger_service
)
if(UNIX)
    target_link_libraries( coroutine_experiments_app PUBLIC Threads::Threads)
endif()
