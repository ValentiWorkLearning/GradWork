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
    PRIVATE
    NordicSDK::Common
)

target_link_libraries(
    platform_delay
    NordicSDK::Common
)