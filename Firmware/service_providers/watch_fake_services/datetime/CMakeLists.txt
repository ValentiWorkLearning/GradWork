add_library(
    datetime_fake_service
    sp_datetime_service_fake.cpp
)

target_include_directories(
    datetime_fake_service
    PRIVATE
    services_ih
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    datetime_fake_service
    PRIVATE
    services_ih
    UtilsLibrary
)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    target_link_libraries(datetime_fake_service
        PRIVATE
        NordicSDK::App::SensorSimulator
        NordicSDK::App::Timer
    )

    target_compile_definitions(
        datetime_fake_service
        PRIVATE
        USE_NRFSDK_SIMULATOR
    )
elseif( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR")
    target_compile_definitions(
        datetime_fake_service
        PRIVATE
        USE_DESKTOP_SIMULATOR
    )
    target_compile_features(
        coroutine_experiments_app
        PRIVATE
        cxx_std_20
    )   

endif()