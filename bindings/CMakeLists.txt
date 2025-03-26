cmake_minimum_required(VERSION 3.15)
project(CapGamBindings)

find_package(pybind11 REQUIRED)

add_library(capgampy MODULE
    call_option.cpp
)

set_target_properties(capgampy PROPERTIES PREFIX "")

set_target_properties(capgampy PROPERTIES CXX_STANDARD 17)

target_link_libraries(capgampy PRIVATE capgam_hello pybind11::module)

if(WIN32)
    set_target_properties(capgampy PROPERTIES SUFFIX ".pyd")
endif()

set_target_properties(capgampy PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/python)
