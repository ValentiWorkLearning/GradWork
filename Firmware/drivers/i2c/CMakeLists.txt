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


target_include_directories(
    i2c
    PRIVATE
    NordicSDK::Common
    UtilsLibrary
)

target_link_libraries(
    i2c
    PRIVATE
    NordicSDK::Common
    UtilsLibrary
)