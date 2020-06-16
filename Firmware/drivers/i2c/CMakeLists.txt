add_library(
    i2c
    i2c_test.cpp
)

target_compile_features(
    i2c
    INTERFACE
    cxx_std_17
)

target_include_directories(
    i2c
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    i2c
    PRIVATE
    UtilsLibrary
    logger_service
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(i2c PRIVATE NordicSDK::Common )

    target_compile_definitions(
        i2c
        PRIVATE
        USE_DEVICE_SPECIFIC
    )
endif()