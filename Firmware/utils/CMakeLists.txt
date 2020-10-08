add_library( UtilsLibrary INTERFACE )

target_compile_features(
    UtilsLibrary
    INTERFACE
    cxx_std_20
)

target_include_directories(
    UtilsLibrary
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

if( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR"  )
    target_compile_definitions(
        UtilsLibrary
        INTERFACE
        USE_DESKTOP_SIMULATOR
        _CRT_SECURE_NO_WARNINGS
    )
elseif( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_compile_options(
        UtilsLibrary
        INTERFACE
        -fcoroutines
    )
endif()

target_link_libraries(
    UtilsLibrary
    INTERFACE
    etl
    logger_service
)
