FILE(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(math_tests ${TEST_SOURCES})

target_link_libraries(math_tests PRIVATE gtest_main capgam_hello)

add_test(NAME math_tests COMMAND math_tests)