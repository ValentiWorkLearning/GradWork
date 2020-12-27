cmake_minimum_required(VERSION 3.14)
project(cppcoro LANGUAGES CXX)

set(CMAKE_CXX_EXTENSIONS OFF)

add_library(cppcoro)
target_sources(cppcoro PRIVATE
	"cppcoro/lib/async_auto_reset_event.cpp"
	"cppcoro/lib/async_manual_reset_event.cpp"
	"cppcoro/lib/async_mutex.cpp"
	"cppcoro/lib/cancellation_state.cpp"
	"cppcoro/lib/cancellation_token.cpp"
	"cppcoro/lib/cancellation_source.cpp"
	"cppcoro/lib/cancellation_registration.cpp"
	"cppcoro/lib/lightweight_manual_reset_event.cpp"
	"cppcoro/lib/ip_address.cpp"
	"cppcoro/lib/ip_endpoint.cpp"
	"cppcoro/lib/ipv4_address.cpp"
	"cppcoro/lib/ipv4_endpoint.cpp"
	"cppcoro/lib/ipv6_address.cpp"
	"cppcoro/lib/ipv6_endpoint.cpp"
	"cppcoro/lib/static_thread_pool.cpp"
	"cppcoro/lib/auto_reset_event.cpp"
	"cppcoro/lib/spin_wait.cpp"
	"cppcoro/lib/spin_mutex.cpp")

if(WIN32)
	target_sources(cppcoro PRIVATE
	    "cppcoro/lib/win32.cpp"
	    "cppcoro/lib/io_service.cpp"
	    "cppcoro/lib/file.cpp"
	    "cppcoro/lib/readable_file.cpp"
	    "cppcoro/lib/writable_file.cpp"
	    "cppcoro/lib/read_only_file.cpp"
	    "cppcoro/lib/write_only_file.cpp"
	    "cppcoro/lib/read_write_file.cpp"
	    "cppcoro/lib/file_read_operation.cpp"
	    "cppcoro/lib/file_write_operation.cpp"
	    "cppcoro/lib/socket_helpers.cpp"
	    "cppcoro/lib/socket.cpp"
	    "cppcoro/lib/socket_accept_operation.cpp"
	    "cppcoro/lib/socket_connect_operation.cpp"
	    "cppcoro/lib/socket_disconnect_operation.cpp"
	    "cppcoro/lib/socket_send_operation.cpp"
	    "cppcoro/lib/socket_send_to_operation.cpp"
	    "cppcoro/lib/socket_recv_operation.cpp"
		"cppcoro/lib/socket_recv_from_operation.cpp")
endif()

target_include_directories(cppcoro PUBLIC 
	$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/cppcoro/include>
)
target_compile_definitions(cppcoro PRIVATE _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING )
target_compile_features(cppcoro PUBLIC cxx_std_20)
target_compile_options( cppcoro PUBLIC /await )