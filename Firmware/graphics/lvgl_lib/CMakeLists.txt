add_subdirectory(lvgl_library)

if( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
    add_subdirectory(lvgl_driver_backend)
endif()