set (TARGET_NAME heartrate_fake_service)

add_library(
    ${TARGET_NAME}
    sp_heartrate_service_fake.cpp
)

target_compile_definitions(
    ${TARGET_NAME}
    PRIVATE
    USE_NRFSDK_SIMULATOR
)

target_include_directories(
    ${TARGET_NAME}
    PRIVATE
    services_ih
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    ${TARGET_NAME}
    PRIVATE
    services_ih
    UtilsLibrary
)

target_link_options(
    ${TARGET_NAME}
    PUBLIC
    ${CPU_FLAGS}
)

target_compile_options(
    ${TARGET_NAME}
    PUBLIC
    $<$<CONFIG:Debug>:-Os>
    $<$<CONFIG:Release>:-Os>
    ${COMMON_FLAGS}
)
