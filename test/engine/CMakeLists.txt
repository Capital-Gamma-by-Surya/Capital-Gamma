FILE(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(engine_tests ${TEST_SOURCES})

target_link_libraries(engine_tests PRIVATE gtest_main capgam_hello)

add_test(NAME engine_tests COMMAND engine_tests)
