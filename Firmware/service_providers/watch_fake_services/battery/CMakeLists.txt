add_library(
    battery_fake_service
    sp_battery_service_fake.cpp
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
    UtilsLibrary
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(battery_fake_service
        PRIVATE
        NordicSDK::App::SensorSimulator
    )

    target_compile_definitions(
        battery_fake_service
        PRIVATE
        USE_NRFSDK_SIMULATOR
    )
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR")
    target_compile_definitions(
        battery_fake_service
        PRIVATE
        USE_DESKTOP_SIMULATOR
    )
endif()