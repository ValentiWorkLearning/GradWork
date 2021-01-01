#Thanks, Alexander-Degtyar/OpenGreenery https://github.com/Alexander-Degtyar/OpenGreenery/blob/master/lib/CMakeLists.txt

set(CMAKE_C_STANDARD 11)
if( ${TARGET_PLATFORM} STREQUAL "FIRMWARE_SIMULATOR" )
	set(CMAKE_CXX_STANDARD 20)
	#add_subdirectory( cppcoro_lib )
elseif( ${TARGET_PLATFORM} STREQUAL "ARM_CORTEX" )
	set(CMAKE_CXX_STANDARD 17)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set( 3RD_PARTY_DIR CACHE STRING ${CMAKE_CURRENT_SOURCE_DIR} )# Libs root path

add_subdirectory( etl )
add_subdirectory( fmt )