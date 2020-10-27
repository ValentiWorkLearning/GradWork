cmake_minimum_required(VERSION 3.14)

project(coroutine_experiments C CXX)

add_executable(coroutine_experiments_app ${PROJECT_SOURCES})

target_sources(
    coroutine_experiments_app
    PRIVATE
    coroutine_thoughts.cpp
)
target_compile_features(
    coroutine_experiments_app
    PRIVATE
    cxx_std_20
)
target_compile_options(
    coroutine_experiments_app
    PRIVATE
    /await
)
target_link_libraries(
    coroutine_experiments_app
    PRIVATE
    drivers_ih
    watch_display
    UtilsLibrary
    logger_service
)