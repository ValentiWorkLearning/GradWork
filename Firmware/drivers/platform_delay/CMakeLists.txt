add_library(
    platform_delay
    delay_provider.cpp
)

target_compile_features(
    platform_delay
    INTERFACE
    cxx_std_17
)

target_include_directories(
    platform_delay
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries( platform_delay PRIVATE NordicSDK::Common )
endif()