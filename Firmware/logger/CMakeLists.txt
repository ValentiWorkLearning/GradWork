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
endif()