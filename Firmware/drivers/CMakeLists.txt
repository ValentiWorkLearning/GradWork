set ( DRIVER_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})


add_subdirectory(headers)
add_subdirectory(platform_delay)
add_subdirectory(factory_impl)
add_subdirectory(i2c)
add_subdirectory(board)
add_subdirectory(gpio)
add_subdirectory(ble)
add_subdirectory(buttons)

add_subdirectory(display)
add_subdirectory(spi)

if( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
    add_subdirectory(winbondflash)
endif()
