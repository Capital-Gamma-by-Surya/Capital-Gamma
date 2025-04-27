cmake_minimum_required(VERSION 3.15)
project(Capital-Gamma VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create a library from "hello" source
add_library(capgam_hello
    src/hello.cpp
    src/instruments/payoffs.cpp
    src/instruments/options_info.cpp
    src/models/equity_price_generator.cpp
    src/engine/mc_option_valuation.cpp
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

if(BUILD_PYTHON_BINDINGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
    add_subdirectory(bindings)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

# Enable testing
option(ENABLE_TESTING "Enable building tests" ON)
if (ENABLE_TESTING)
    enable_testing()
    add_subdirectory(test)
endif()
