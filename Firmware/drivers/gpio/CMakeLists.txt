add_library(
    gpio
    gpio_pin.cpp
)

target_include_directories(
    gpio
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    gpio
    PRIVATE
    UtilsLibrary
    logger_service
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_compile_definitions(gpio PRIVATE USE_DEVICE_SPECIFIC)
    target_link_libraries(gpio PRIVATE NordicSDK::Common )
endif()