add_library(
    windbond_spi_flash_driver
    INTERFACE
)

target_include_directories(
    windbond_spi_flash_driver
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/inc
)