cmake_minimum_required(VERSION 3.15)

project(CapGamLowLatency)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/main.cpp)
