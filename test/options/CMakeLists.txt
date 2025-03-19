FILE(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(payoff_tests ${TEST_SOURCES})

target_link_libraries(payoff_tests PRIVATE gtest_main capgam_hello)

add_test(NAME payoff_tests COMMAND payoff_tests)
