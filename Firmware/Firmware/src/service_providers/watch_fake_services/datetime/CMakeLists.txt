add_library(
    datetime_fake_service
    sp_datetime_service_fake.cpp
)

target_compile_definitions(
    datetime_fake_service
    PRIVATE
    USE_NRFSDK_SIMULATOR
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
    NordicSDK::App::SensorSimulator
    NordicSDK::App::Timer
    UtilsLibrary
)

target_compile_options(
    datetime_fake_service
    PUBLIC
    $<$<CONFIG:Debug>:-Os>
    $<$<CONFIG:Release>:-Os>
    ${COMMON_FLAGS}
)
