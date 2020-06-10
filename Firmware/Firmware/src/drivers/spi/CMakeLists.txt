add_library(
    spi
    spi_wrapper.cpp
)

target_include_directories(
    spi
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${NRF_SDK_DIRECTORY}
)

target_link_libraries(
    spi
    INTERFACE
    ${NRF_SDK_DIRECTORY}/NordicSDK::Common
)