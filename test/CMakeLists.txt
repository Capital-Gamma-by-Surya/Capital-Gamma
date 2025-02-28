cmake_minimum_required(VERSION 3.15)

# Download Google Test via FetchContent
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(test_hello
	test_hello.cpp
)

# Link with gtest and library
target_link_libraries(test_hello
	PRIVATE
		gtest_main
		capgam_hello
)

add_test(NAME test_hello COMMAND test_hello)