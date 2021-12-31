add_executable(
ArticleExample
root.cpp
)

target_include_directories(
	ArticleExample
	PRIVATE
	${CMAKE_CURRENT_LIST_DIR}
)

target_compile_features(
	ArticleExample
    PUBLIC
    cxx_std_20
)

target_compile_options(ArticleExample PUBLIC $<$<CXX_COMPILER_ID:GNU>:-fcoroutines>)
