

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
)