add_library(
    heartrate_fake_service
    sp_heartrate_service_fake.cpp
)

target_compile_definitions(
    heartrate_fake_service
    PRIVATE
    USE_NRFSDK_SIMULATOR
)

target_include_directories(
    heartrate_fake_service
    PRIVATE
    services_ih
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    heartrate_fake_service
    PRIVATE
    services_ih
    UtilsLibrary
)