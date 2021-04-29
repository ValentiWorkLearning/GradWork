if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    
    add_library(
        spi
        spi_wrapper.cpp
        spi_wrapper_async.cpp
    )

    target_link_libraries( spi PRIVATE NordicSDK::Common )
    target_compile_options(
    spi
    PRIVATE
    -fcoroutines
)
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )

    add_library(
        spi
        spi_wrapper_stub.cpp
    )
endif()


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
    fmt
    logger_service
)
target_compile_features(
    spi
    PRIVATE
    cxx_std_20
)
