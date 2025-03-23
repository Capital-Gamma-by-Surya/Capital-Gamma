FILE(GLOB TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(models_tests ${TEST_SOURCES})

target_link_libraries(models_tests PRIVATE gtest_main capgam_hello)

add_test(NAME models_tests COMMAND models_tests)
