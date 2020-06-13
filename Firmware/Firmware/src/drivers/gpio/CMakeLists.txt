add_library(
    gpio
    gpio_pin.cpp
)

target_compile_features(
    gpio
    INTERFACE
    cxx_std_17
)

target_include_directories(
    gpio
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)


target_include_directories(
    gpio
    PRIVATE
    NordicSDK::Common
    UtilsLibrary
)

target_link_libraries(
    gpio
    PRIVATE
    NordicSDK::Common
    UtilsLibrary
)