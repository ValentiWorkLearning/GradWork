
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


find_program( NRFJPROG NAMES nrfjprog PATHS $ENV{NRFJPROG_PATH} )

function( nordicSdk_flashSoftDevice SOFTDEVICE_PATH NRF_TARGET )
    add_custom_target(FLASH_ERASE ALL
        COMMAND sleep 0.5s
        COMMAND ${NRFJPROG} --eraseall -f ${NRF_TARGET}
        COMMENT "erasing flashing"
    )
    add_custom_target(FLASH_SOFTDEVICE ALL
        DEPENDS ${EXECUTABLE_NAME} FLASH_ERASE
        COMMAND ${NRFJPROG} --program ${SOFTDEVICE_PATH} -f ${NRF_TARGET} --sectorerase
        COMMAND sleep 1s
        COMMAND ${NRFJPROG} --reset -f ${NRF_TARGET}
        COMMENT "flashing SoftDevice"
    )
endfunction(nordicSdk_flashSoftDevice)

function(nordicSdk_flashFirmware EXECUTABLE_NAME )
    add_custom_target("FLASH_${EXECUTABLE_NAME}" ALL
        DEPENDS ${EXECUTABLE_NAME} FLASH_ERASE FLASH_SOFTDEVICE
        COMMAND ${NRFJPROG} --program ${EXECUTABLE_NAME}.hex -f ${NRF_TARGET} --sectorerase
        COMMAND sleep 0.5s
        COMMAND ${NRFJPROG} --reset -f ${NRF_TARGET}
        COMMENT "flashing ${EXECUTABLE_NAME}.hex"
    )
endfunction(nordicSdk_flashFirmware )
