FILE(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(instruments_tests ${TEST_SOURCES})

target_link_libraries(instruments_tests PRIVATE gtest_main capgam_hello)

add_test(NAME instruments_tests COMMAND instruments_tests)
