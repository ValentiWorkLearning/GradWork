add_library(
    battery_fake_service
    sp_battery_service_fake.cpp
)

target_compile_definitions(
    battery_fake_service
    PRIVATE
    USE_NRFSDK_SIMULATOR
)

target_include_directories(
    battery_fake_service
    PRIVATE
    services_ih
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    battery_fake_service
    PRIVATE
    services_ih
    NordicSDK::App::SensorSimulator
    UtilsLibrary
)