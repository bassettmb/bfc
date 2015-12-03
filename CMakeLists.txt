cmake_minimum_required(VERSION 2.6)

project(bfc)

set(bfc_VERSION_MAJOR 0)
set(bfc_VERSION_MINOR 2)
set(bfc_VERSION_PATCH 0)

option(TEST "Build all tests." OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra -Wno-unused-parameter")

include_directories(${bfc_SOURCE_DIR})

add_subdirectory(ast)
add_subdirectory(pprint)

add_executable(bfc main.cpp)
target_link_libraries(bfc ast pprint)


# If we're running unit tests:
if (TEST)

  # Add the googletest framework to the source tree
  add_subdirectory(googletest EXCLUDE_FROM_ALL)
  enable_testing()
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

  add_subdirectory(test EXCLUDE_FROM_ALL)

endif()
