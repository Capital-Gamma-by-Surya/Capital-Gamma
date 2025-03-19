FILE(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(options_tests ${TEST_SOURCES})

target_link_libraries(options_tests PRIVATE gtest_main capgam_hello)

add_test(NAME options_tests COMMAND options_tests)
