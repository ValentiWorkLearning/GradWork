add_library(
    logger_service
    logger_service_impl.cpp
)

target_include_directories(
    logger_service
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
    UtilsLibrary
)

target_compile_features(
    logger_service
    PUBLIC
    cxx_std_20
)

target_link_libraries(
    logger_service
    PUBLIC
    UtilsLibrary
    PRIVATE
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )

    target_compile_definitions(
        logger_service
        PRIVATE
        LoggerSegger
    )

    target_link_libraries(logger_service
        PRIVATE
        NordicSDK::Common
    )
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
    target_compile_definitions(
        logger_service
        PRIVATE
        LoggerDesktop
    )
    target_link_libraries(
        logger_service
        PRIVATE
        fmt::fmt
    )
endif()