if(WIN32 OR UNIX AND ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR")
    find_package(spdlog REQUIRED)
endif()

add_library(watch_filesystem INTERFACE

    filesystem/filesystem_holder.hpp
    filesystem/block_device_wrapper/combiner_block_device.hpp
)

target_sources(watch_filesystem INTERFACE
    filesystem/block_device_wrapper/ih_block_device.hpp
    filesystem/block_device_wrapper/heap_block_device.hpp
    filesystem/block_device_wrapper/adaptor_block_device.hpp
    filesystem/block_device_wrapper/spi_block_device.hpp
)

target_include_directories(watch_filesystem INTERFACE ${CMAKE_CURRENT_LIST_DIR} )

target_link_libraries(watch_filesystem INTERFACE
    littlefs
)

if(WIN32 OR UNIX AND ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
    target_link_libraries(watch_filesystem INTERFACE spdlog::spdlog)
endif()

target_link_libraries(
    watch_filesystem INTERFACE
    drivers_ih
    windbond_spi_flash_driver
)