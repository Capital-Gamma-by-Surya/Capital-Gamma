cmake_minimum_required(VERSION 3.15)
project(Capital-Gamma VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# Create a library from "hello" source
add_library(capgam_hello
    src/hello.cpp
    src/math/primative_operator.cpp
    src/options/payoffs.cpp
)

# Add header path for library
target_include_directories(capgam_hello
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Create an executable (the main application) 
add_executable(cap_gam_main
    src/main.cpp
)

# Link our library into the main executable
target_link_libraries(cap_gam_main PRIVATE capgam_hello)

# Enable testing
option(ENABLE_TESTING "Enable building tests" ON)
if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
