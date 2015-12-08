cmake_minimum_required(VERSION 2.8.12)

project(bfc)

option(NO_VERIFY_COMPILER "assume that compiler configuration is correct" OFF)

set(bfc_VERSION_MAJOR 0)
set(bfc_VERSION_MINOR 3)
set(bfc_VERSION_PATCH 0)

if(NOT(NO_VERIFY_COMPILER))
  if("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    if(NOT("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 3.5))
      set(CMAKE_CXX_FLAGS
          "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra \
          -Wno-unused-parameter -Wno-unused-function -Werror=return-type")
    else()
      message(FATAL_ERROR "c++14 compiler support required")
    endif()
  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
    if(NOT("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 5.0))
      set(CMAKE_CXX_FLAGS
          "${CMAKE_CXX_FLAGS} -std=c++14 -g -Wall -Wextra \
          -Wno-unused-parameter -Wno-unused-function -Werror=return-type")
    else()
      message(FATAL_ERROR "c++14 compiler support required")
    endif()
  elseif("${CMAKE_CXX_COMPILER_ID}" MATCHES "MSVC")
    if("${CMAKE_CXX_COMPILER_VERSION}" VERSION_LESS 19)
      message(FATAL_ERROR "c++14 compiler support required")
    endif()
  else()
    message(FATAL_ERROR "c++14 compiler support required")
  endif()
endif()

include_directories(${bfc_SOURCE_DIR})

add_subdirectory(ast)
add_subdirectory(pprint)
add_subdirectory(rts)

add_executable(bfc main.cpp)
target_link_libraries(bfc ast pprint)

enable_testing()
# Add the googletest framework to the source tree
add_subdirectory(googletest EXCLUDE_FROM_ALL)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_custom_target(check "${CMAKE_CTEST_COMMAND}" -V)
add_subdirectory(test EXCLUDE_FROM_ALL)
