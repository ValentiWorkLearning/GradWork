
add_library( testing_common INTERFACE )

target_link_libraries(testing_common INTERFACE UtilsLibrary)
target_include_directories(testing_common INTERFACE ${CMAKE_CURRENT_LIST_DIR}/inc)
