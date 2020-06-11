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
)
