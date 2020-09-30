add_library(
    spi
    spi_wrapper.cpp
    spi_wrapper_async.cpp
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
target_compile_features(
    spi
    PRIVATE
    cxx_std_20
)

target_compile_options(
    spi
    PRIVATE
    -fcoroutines
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries( spi PRIVATE NordicSDK::Common )
endif()