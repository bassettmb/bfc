cmake_minimum_required(VERSION 3.0)

project(bfc)

set(bfc_VERSION_MAJOR 0)
set(bfc_VERSION_MINOR 0)
set(bfc_VERSION_PATCH 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra -Wno-unused-parameter")

include_directories(${bfc_SOURCE_DIR})

add_subdirectory(ast)
add_subdirectory(pprint)

add_executable(bfc main.cpp)
