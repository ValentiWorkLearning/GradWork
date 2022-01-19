if(WIN32 OR UNIX)
    find_package(spdlog REQUIRED)
endif()

add_library(filesystem INTERFACE filesystem/filesystem_holder.hpp)

target_sources(filesystem INTERFACE
    filesystem/block_device_wrapper/ih_block_device.hpp
    filesystem/block_device_wrapper/heap_block_device.hpp
    filesystem/block_device_wrapper/adaptor_block_device.hpp
)

target_include_directories(filesystem INTERFACE ${CMAKE_CURRENT_LIST_DIR} )

target_link_libraries(filesystem INTERFACE
    littlefs
)

if(WIN32 OR UNIX)
    target_link_libraries(filesystem INTERFACE spdlog::spdlog)
endif()