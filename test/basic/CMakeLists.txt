file(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(basic_tests ${TEST_SOURCES})

# Link with gtest and library
target_link_libraries(basic_tests
	PRIVATE
		gtest_main
		capgam_hello
)

add_test(NAME basic_tests COMMAND basic_tests)