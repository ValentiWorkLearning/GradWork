

add_subdirectory(battery)
add_subdirectory(datetime)
add_subdirectory(heartrate)

add_library(
    watch_fake_services
    sp_fake_services_creator.cpp
)

target_include_directories(
    watch_fake_services
    PRIVATE
    services_ih
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    watch_fake_services
    PRIVATE
    services_ih
    UtilsLibrary
    etl
    battery_fake_service
    datetime_fake_service
    heartrate_fake_service
)

target_link_options(
    watch_fake_services
    PUBLIC
    ${CPU_FLAGS}
)

target_compile_options(
    watch_fake_services
    PUBLIC
    $<$<CONFIG:Debug>:-Os>
    $<$<CONFIG:Release>:-Os>
    ${COMMON_FLAGS}
)
target_compile_features( watch_fake_services PUBLIC cxx_std_20 )