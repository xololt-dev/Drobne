cmake_minimum_required(VERSION 3.11)
project(drobne VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) # Consider C++23
set(CMAKE_CXX_STANDARD_REQUIRED True)

###########
# Testing #
###########
# include(CTest)
# enable_testing()

###########
# Project #
###########
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/*.cpp" "${CMAKE_SOURCE_DIR}/*/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(drobne PUBLIC "${PROJECT_BINARY_DIR}")
