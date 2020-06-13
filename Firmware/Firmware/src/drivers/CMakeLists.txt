set ( DRIVER_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_subdirectory(spi)
add_subdirectory(ih)
#add_subdirectory(ble)
add_subdirectory(display)
add_subdirectory(gpio)
add_subdirectory(platform_delay)
# add_subdirectory(winbondflash)