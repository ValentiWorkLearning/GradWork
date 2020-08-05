project(FirmwareTesting LANGUAGES CXX)

enable_testing()
include(GoogleTest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set (3RDPARTY_DIR "../3rdparty")
add_subdirectory( ${3RDPARTY_DIR}/googletest "3rdparty/googletest")

add_executable(
    ${PROJECT_NAME}
    main.cpp
    clock_page_view_handler_test.cpp
    clock_page_handler_fixture.hpp
    buttons_driver_test.cpp
    buttons_fixture.hpp
    buttons_fake_event_handler.hpp)

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

target_link_libraries(
    ${PROJECT_NAME}
    gtest
    gmock
    gtest_main

    watch_graphics
    lvgl_lib
    drivers_ih
    buttons_driver
    UtilsLibrary
)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC
    cxx_std_20
)

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})