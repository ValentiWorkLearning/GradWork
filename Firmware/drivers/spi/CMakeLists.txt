add_library(
    spi
    spi_wrapper.cpp
)

target_compile_features(
    spi
    INTERFACE
    cxx_std_17
)

target_include_directories(
    spi
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    spi
    PRIVATE
    NordicSDK::Common
    UtilsLibrary
    drivers_ih
    etl
)