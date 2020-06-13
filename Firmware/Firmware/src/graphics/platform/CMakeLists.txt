add_library(
    graphics_backend
    gs_platform_layer.cpp
)


target_compile_definitions(
    graphics_backend
    PRIVATE
    USE_ST7789V_BACKEND
)

target_link_libraries(
    graphics_backend
    PRIVATE
    NordicSDK::Common
    lvgl_lib
    UtilsLibrary
    logger_service
    drivers_ih
    etl
)

