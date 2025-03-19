cmake_minimum_required(VERSION 3.15)

# Download Google Test via FetchContent
include(FetchContent)
FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
)

FetchContent_MakeAvailable(googletest)

add_subdirectory(basic)
add_subdirectory(maths)
add_subdirectory(options)
