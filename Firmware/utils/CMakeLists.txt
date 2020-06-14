add_library( UtilsLibrary INTERFACE )

target_compile_features(
    UtilsLibrary
    INTERFACE
    cxx_std_17
)

target_include_directories(
    UtilsLibrary
    INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/inc
)

target_link_libraries(
    UtilsLibrary
    INTERFACE
    etl
)
