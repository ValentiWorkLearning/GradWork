add_library(
    watchboard
    watchboard.cpp
)

target_compile_definitions(
    watchboard
    PUBLIC
    USE_DEVICE_SPECIFIC
)
target_include_directories(
    watchboard
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)


target_include_directories(
    watchboard
    PRIVATE
    NordicSDK::Common
    UtilsLibrary
)

target_link_libraries(
    watchboard
    PRIVATE
    NordicSDK::Common
    NordicSDK::Bsp
    NordicSDK::App::Timer
    UtilsLibrary
    logger_service
    platform_delay
)