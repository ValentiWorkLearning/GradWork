function(declareNordicSdkLibrary LIBRARY_NAME INCLUDES_LIST SOURCES_LIST DEPENDS_ON)

    set (TARGET_HEADER_LIST ${INCLUDES_LIST} )
    set( LIBRARY_NAME_COPY ${LIBRARY_NAME} )

    list(APPEND ${TARGET_HEADER_LIST} ${DEPENDS_ON})
    #cmake_print_variables( ${TARGET_HEADER_LIST} ${INCLUDES_LIST})
    add_library( ${LIBRARY_NAME_COPY} STATIC ${SOURCES_LIST} ${TARGET_HEADER_LIST} )

    target_include_directories(
        ${LIBRARY_NAME}
        PUBLIC
        ${INCLUDES_LIST}
        PRIVATE
        ${DEPENDS_ON}
    )

    target_compile_definitions(
        ${LIBRARY_NAME}
        PUBLIC
        ${NordicCompileDefinitions}
    )

    # set (DEPENDENCIES_LIST)
    # foreach(DEPENDENCY in ${DEPENDS_ON})
    #     list(APPEND ${DEPENDENCIES_LIST} ${DEPENDENCY} )
    # endforeach()

    target_link_libraries(
        ${LIBRARY_NAME}
        PUBLIC
        ${DEPENDS_ON}
    )

    string( FIND ${LIBRARY_NAME_COPY} "_" ALIAS_MARKER_INDEX )
    if( NOT( ${ALIAS_MARKER_INDEX} EQUAL "-1" ) )
        string(REPLACE "_" "::" ALIAS_CORRECTED ${LIBRARY_NAME_COPY} )
    else()
        set( ALIAS_CORRECTED ${LIBRARY_NAME_COPY} )
    endif()

    set( CORRECTED_ALIAS_NAME NordicSDK::${ALIAS_CORRECTED} )
    #cmake_print_variables( ${CORRECTED_ALIAS_NAME} )

    add_library( NordicSDK::${ALIAS_CORRECTED} ALIAS ${LIBRARY_NAME_COPY})

    # target_sources(
    #     ${LIBRARY_NAME_COPY}
    #     INTERFACE
    #     ${SOURCES_LIST}
    # )

endfunction(declareNordicSdkLibrary SOURCES_LIST DEPENDS_ON)
