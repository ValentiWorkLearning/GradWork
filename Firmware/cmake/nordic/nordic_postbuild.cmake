
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
    set(TERMINAL "open")
elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Windows")
    set(TERMINAL "sh")
else()
    set(TERMINAL "gnome-terminal")
endif()

function (nordicSdk_createBinAndHexFiles TARGET_NAME)
    add_custom_command(TARGET ${TARGET_NAME}
        POST_BUILD
        COMMAND ${CMAKE_SIZE_UTIL} ${TARGET_NAME}.out
        COMMAND ${CMAKE_OBJCOPY} -O binary ${TARGET_NAME}.out "${TARGET_NAME}.bin"
        COMMAND ${CMAKE_OBJCOPY} -O ihex ${TARGET_NAME}.out "${TARGET_NAME}.hex"
        COMMENT "post build steps for ${TARGET_NAME}"
    )
endfunction()
