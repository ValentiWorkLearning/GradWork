add_library(
    spi
    spi_wrapper.cpp
)

target_include_directories(
    spi
    PUBLIC
    NordicSDK::Common
    UtilsLibrary
)

target_link_libraries(
    spi
    PUBLIC
    NordicSDK::Common
    UtilsLibrary
)