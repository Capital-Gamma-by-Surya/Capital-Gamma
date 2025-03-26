FILE(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(model_tests ${TEST_SOURCES})

target_link_libraries(model_tests PRIVATE gtest_main capgam_hello)

add_test(NAME model_tests COMMAND model_tests)
