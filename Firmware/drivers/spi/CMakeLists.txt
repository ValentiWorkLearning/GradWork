add_library(
    spi
    spi_wrapper.cpp
)

target_include_directories(
    spi
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    spi
    PRIVATE
    UtilsLibrary
    drivers_ih
    etl
)
if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries( spi PRIVATE NordicSDK::Common )
endif()