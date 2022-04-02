add_library(
    spi
    INTERFACE
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries( spi INTERFACE NordicSDK::Common )
endif()

target_compile_options(
    spi
    INTERFACE
    $<$<CXX_COMPILER_ID:GNU>:-fcoroutines>
)

target_include_directories(
    spi
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/inc
    ${CMAKE_CURRENT_LIST_DIR}/inc/backends
)

target_link_libraries(
    spi
    INTERFACE
    UtilsLibrary
    etl
    logger_service
)
target_compile_features(
    spi
    INTERFACE
    cxx_std_20
)
