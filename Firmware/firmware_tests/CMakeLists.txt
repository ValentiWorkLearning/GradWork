project(FirmwareTesting LANGUAGES CXX)


include(GoogleTest)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

set(CMAKE_CXX_STANDARD 20)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

enable_testing()
find_package(GTest REQUIRED)
add_subdirectory(coroutine)
add_subdirectory(article_example)

add_executable(
    ${PROJECT_NAME}
    
    buttons_driver/buttons_driver_test.cpp

    clock_page_handler/clock_page_view_handler_test.cpp

    main_window/mainwindow_model_test.cpp

    stubs/pages_stub_pages_creator.cpp
    stubs/widgets_stub_pages_creator.cpp

    drivers/spi/spi_driver_fixture.hpp
    drivers/spi/spi_fake_backend.hpp
    drivers/spi/spi_driver_test_suite.cpp

    drivers/windond_flash/flash_driver_test_suite.cpp
    drivers/windond_flash/flash_fixture.hpp
    drivers/spi/mock_gpio.hpp
    drivers/spi/mock_spi.hpp
)

mark_as_advanced(
    BUILD_GMOCK BUILD_GTEST BUILD_SHARED_LIBS
    gmock_build_tests gtest_build_samples gtest_build_tests
    gtest_disable_pthreads gtest_force_shared_crt gtest_hide_internal_symbols
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    stubs
    stubs/pages
    stubs/widgets
)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
    GTest::gmock_main
    UtilsLibrary

    watch_graphics
    watch_display
    lvgl_lib
    drivers_ih

    buttons_driver
    windbond_spi_flash_driver
)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC
    cxx_std_20
)

gtest_discover_tests(${PROJECT_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})